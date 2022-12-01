#include <systemcommands.hpp>

#include <ipmid/api.hpp>
#include <ipmid/utils.hpp>
#include <phosphor-logging/log.hpp>

namespace ipmi
{
    static void registerOEMFunctions() __attribute__((constructor));

    ipmi::RspType<uint8_t, // direction
                  uint8_t  // value
                  >
        ipmiGetGpioState(uint8_t pin_number)
    {
        if (pin_number > 231)
        {
            return ipmi::responseParmOutOfRange();
        }

        return ipmi::responseSuccess(0x1, 0x0);
    }

    ipmi::RspType<> ipmiSetGpioState(uint8_t pin_number, uint8_t pin_dir, uint8_t pin_value)
    {
        return ipmi::responseSuccess();
    }

    static void registerOEMFunctions(void)
    {
        phosphor::logging::log<phosphor::logging::level::INFO>(
            "Registering OEM commands");

        // <Get OEM command test>
        ipmi::registerHandler(ipmi::prioOpenBmcBase, ipmi::netFnOemFour,
                            cmdSYSGpioGet,
                            ipmi::Privilege::User, ipmiGetGpioState);

        // <Set OEM command test>
        ipmi::registerHandler(ipmi::prioOpenBmcBase, ipmi::netFnOemFour,
                            cmdSYSGpioSet,
                            ipmi::Privilege::User, ipmiSetGpioState);
    }

} // namespace ipmi
