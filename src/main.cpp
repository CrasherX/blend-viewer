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

    std::vector<std::string>* types = nullptr;
    const std::vector<uint16_t>* lengths = nullptr;

    const std::vector<blender_blend_t::file_block_t*>* blocks = blend.blocks();
    for (const auto block : *blocks) {
        if (block->code() == "DNA1") {
            const blender_blend_t::dna1_body_t* dna1_body = block->body();
            types = dna1_body->types();
            lengths = dna1_body->lengths();
        }
    }

    for (const auto block : *blocks) {
        if (block->code().substr(0, 2) == "ME") {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            const blender_blend_t::dna_struct_t* dna_struct = block->sdna_struct();
            const std::vector<blender_blend_t::dna_field_t*>* dna_fields = dna_struct->fields();

            uint8_t* dst = new uint8_t[block->_raw_body().length()];
            std::memcpy(dst, block->_raw_body().c_str(), block->_raw_body().length());

            std::size_t pos = 0;
            for (const auto field : *dna_fields) {
                std::vector<std::string>::iterator it = std::find(types->begin(), types->end(), field->type());
                uint datalen = lengths->at(distance(types->begin(), it));
                if (field->name()[0] == '*') {
                    datalen = sizeof(uint8_t*);
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

                if (field->name() == "loc[3]") {
                    float loc[3];
                    std::memcpy(loc, dst + pos, datalen);

                    std::cout << "loc[0] " << loc[0] << std::endl;
                    std::cout << "loc[1] " << loc[1] << std::endl;
                    std::cout << "loc[2] " << loc[2] << std::endl;
                }

                if (field->name() == "size[3]") {
                    float size[3];
                    std::memcpy(size, dst + pos, datalen);

                    std::cout << "size[0] " << size[0] << std::endl;
                    std::cout << "size[1] " << size[1] << std::endl;
                    std::cout << "size[2] " << size[2] << std::endl;
                }

                if (field->name() == "vdata") {

                    std::cout << block->_raw_body().substr(pos, datalen) << std::endl;
                }

                std::cout << field->type() << "\t"
                          << field->name() << "\t"
                          << datalen << "\t"
                          // << block->_raw_body().substr(pos, datalen)
                          << std::endl;

                pos += datalen;
            }

            delete[] dst;
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
