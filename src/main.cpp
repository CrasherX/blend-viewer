#include "MainView.h"
#include "QApplication"
#include "QTimer"
#include "algorithm"
#include "blender_blend.h"
#include "cstring"
#include "filesystem"
#include "fstream"
#include "iostream"
#include "kaitai/kaitaistream.h"
#include "map"
#include "string"

typedef struct {
    float co[3];
    int16_t no[3];
    uint8_t flag;
    uint8_t bweight;
} MVert;

typedef struct {
    uint32_t v1;
    uint32_t v2;
    uint8_t crease;
    uint8_t bweight;
    uint16_t flag;
} MEdge;

typedef struct {
    std::vector<MEdge> medges;
    std::vector<MVert> mverts;
} Mesh;

template <typename K, typename V>
void printMap(std::map<K, V> map)
{
    for (const auto& [key, val] : map) {
        std::cout << "[" << key << "] = " << val << "," << std::endl;
    }
}

void loadModel(void)
{
    std::ifstream input("../models/smiltis.blend", std::ifstream::binary);
    kaitai::kstream ks(&input);
    blender_blend_t blend(&ks);
    uint8_t pointer_size = (uint8_t)blend.hdr()->psize();

    std::vector<std::string>* types = nullptr;
    const std::vector<uint16_t>* lengths = nullptr;

    const std::vector<blender_blend_t::file_block_t*>* blocks = blend.blocks();
    for (const auto block : *blocks) {
        if (block->code() == "DNA1") {
            const blender_blend_t::dna1_body_t* dna1_body = block->body();
            types = dna1_body->types();
            lengths = dna1_body->lengths();
            break;
        }
    }

    std::vector<Mesh> meshes;
    void* old_mvert = nullptr;
    void* old_medge = nullptr;
    int totvert = 0;
    int totedge = 0;
    for (const auto block : *blocks) {
        if (block->code().substr(0, 2) == "ME") {
            Mesh mesh;
            meshes.push_back(mesh);

            //            uint64_t temp = 0;
            //            for (unsigned i = 0; i < pointer_size; ++i) {
            //                uint8_t b = block->mem_addr()[i];
            //                temp |= ((uint64_t)b << (i * 8));
            //            }
            //            uint8_t* oldmemaddr = (uint8_t*)temp;

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

            uint8_t* raw = new uint8_t[block->_raw_body().length()];
            std::memcpy(raw, block->_raw_body().c_str(), block->_raw_body().length());
            std::size_t pos = 0;
            const blender_blend_t::dna_struct_t* dna_struct = block->sdna_struct();
            const std::vector<blender_blend_t::dna_field_t*>* dna_fields = dna_struct->fields();
            for (const auto field : *dna_fields) {
                std::vector<std::string>::iterator it = std::find(types->begin(), types->end(), field->type());
                uint datalen = lengths->at(distance(types->begin(), it));

                if (field->name()[0] == '*') {
                    std::cout << "actual size " << datalen << std::endl;
                    datalen = pointer_size;
                }

                if (field->name()[field->name().length() - 1] == ']') {
                    for (unsigned i = 0; i < field->name().length(); ++i) {
                        if (field->name().at(i) == '[') {
                            auto str = field->name().substr(i + 1, field->name().length() - i - 2);
                            unsigned long arrlen = std::stoul(str);
                            datalen = arrlen * datalen;
                            break;
                        }
                    }
                }

                if (field->name() == "*mvert") {
                    std::memcpy(&old_mvert, raw + pos, pointer_size);
                }

                if (field->name() == "*medge") {
                    std::memcpy(&old_medge, raw + pos, pointer_size);
                }

                if (field->name() == "edata") {
                    void* layers;
                    int totlayer;
                    int maxlayer;
                    int totsize;
                    int pad;
                    void* pool;

                    std::memcpy(&layers, raw + pos, pointer_size);
                    std::memcpy(&totlayer, raw + pos + pointer_size, 4);
                    std::memcpy(&maxlayer, raw + pos + pointer_size + 4, 4);
                    std::memcpy(&totsize, raw + pos + pointer_size + 8, 4);
                    std::memcpy(&pad, raw + pos + pointer_size + 12, 4);
                    std::memcpy(&pool, raw + pos + pointer_size + 16, 4);

                    std::cout << "layers " << layers << std::endl;
                    std::cout << "totlayer " << totlayer << std::endl;
                    std::cout << "maxlayer " << maxlayer << std::endl;
                    std::cout << "totsize " << totsize << std::endl;
                    std::cout << "pad " << pad << std::endl;
                }

                if (field->name() == "totvert") {
                    std::memcpy(&totvert, raw + pos, datalen);
                }

                if (field->name() == "totedge") {
                    std::memcpy(&totedge, raw + pos, datalen);
                }

                if (field->name() == "loc[3]") {
                    float loc[3];
                    std::memcpy(loc, raw + pos, datalen);

                    std::cout << "loc[0] " << loc[0] << std::endl;
                    std::cout << "loc[1] " << loc[1] << std::endl;
                    std::cout << "loc[2] " << loc[2] << std::endl;
                }

                if (field->name() == "size[3]") {
                    float size[3];
                    std::memcpy(size, raw + pos, datalen);

                    std::cout << "size[0] " << size[0] << std::endl;
                    std::cout << "size[1] " << size[1] << std::endl;
                    std::cout << "size[2] " << size[2] << std::endl;
                }

                std::cout << field->type() << "\t"
                          << field->name() << "\t"
                          << datalen << "\t"
                          // << block->_raw_body().substr(pos, datalen)
                          << std::endl
                          << std::endl;

                pos += datalen;
            }
            delete[] raw;
        }

        void* addr;

        addr = 0;
        std::memcpy(&addr, block->mem_addr().c_str(), pointer_size);
        if (addr == old_mvert) {
            MVert* mvert;
            for (int i = 0; i < totvert; ++i) {
                std::string sub = block->_raw_body().substr(i * sizeof(MVert), sizeof(MVert));
                mvert = ((MVert*)(sub.c_str()));

                MVert m;
                m.co[0] = mvert->co[0];
                m.co[1] = mvert->co[1];
                m.co[2] = mvert->co[2];

                m.no[0] = mvert->no[0];
                m.no[1] = mvert->no[1];
                m.no[2] = mvert->no[2];
                meshes.back().mverts.push_back(m);
            }
        }

        addr = 0;
        std::memcpy(&addr, block->mem_addr().c_str(), pointer_size);
        if (addr == old_medge) {
            MEdge* medge;
            for (int i = 0; i < totedge; ++i) {
                medge = ((MEdge*)(block->_raw_body().substr(i * sizeof(MEdge), sizeof(MEdge)).c_str()));

                MEdge m;
                m.v1 = medge->v1;
                m.v2 = medge->v2;
                meshes.back().medges.push_back(m);
            }
        }
    }
    std::cout << "ok" << std::endl;
    for (auto ms : meshes) {
        std::cout << std::endl
                  << "Mesh!" << std::endl;
        for (auto mvert : ms.mverts) {
            std::cout << "Vert " << mvert.co[0] << " " << mvert.co[1] << " " << mvert.co[2] << " " << std::endl;
            //            std::cout << mvert.no[0] << " " << mvert.no[1] << " " << mvert.no[2] << " " << std::endl
            //                      << std::endl;
        }
        for (auto medge : ms.medges) {
            std::cout << "Edge " << medge.v1 << " " << medge.v2 << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainView mainView;
    mainView.show();

    loadModel();

    return app.exec();
}
