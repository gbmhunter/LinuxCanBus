#include <string>
#include <vector>

#include "LinuxCanBus/StrConv.hpp"

namespace mn {
    namespace LinuxCanBus {

/// \brief      Protocol agnostic representation of an extended CAN message.
/// \details    Converted to platform-specific data objects in the non-abstract CanBus objects.
        class CanMsg {

        public:

            CanMsg() {
                ClearAll();
            }

            void ClearAll() {
                arbitrationField_.address = 0;
                data_.clear();
            }

            std::string ToString() const {
                std::stringstream output;
                output << "{ address = " << CppUtils::StrConv::ToHex(arbitrationField_.address, 8);
                for (size_t i = 0; i < data_.size(); i++) {
                    output << ", data[" << std::to_string(i) << "] = " << CppUtils::StrConv::ToHex(data_[i], 2);

                }
                output << " }";
                return output.str();
            }

            typedef struct {
                uint32_t address : 29; // [0:28]
            } ArbitrationField;
            ArbitrationField arbitrationField_;

            std::vector<uint8_t> data_;

            /// \brief      Get the extended address from the arbitration field.
            uint32_t GetAddress() {
                return arbitrationField_.address;
            }

            /// \brief      Set the extended address in the arbitration field.
            void SetAddress(uint32_t address) {
                arbitrationField_.address = address;
            }

        protected:

        };

    }
}
