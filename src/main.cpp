#include <iostream>
#include <libusb-1.0/libusb.h>

void printdev(libusb_device* const _dev, ssize_t _index)
{
    libusb_device_descriptor desc;
    int error = libusb_get_device_descriptor(_dev, &desc);
    if (error < 0)
    {
        std::cerr << "failed to get device descriptor" << std::endl;
        return;
    }

    std::cout << _index << ": Number of possible configurations: " <<  static_cast<int>(desc.bNumConfigurations) << "  ";
    std::cout << "Device Class: " <<  static_cast<int>(desc.bDeviceClass) << "  ";
    std::cout << "VendorID: " << desc.idVendor << "  ";
    std::cout << "ProductID: " << desc.idProduct << std::endl;

    libusb_config_descriptor* config = nullptr;
    libusb_get_config_descriptor(_dev, 0, &config);
    if(config != nullptr)
    {
        std::cout << "\tInterfaces: " <<  static_cast<int>(config->bNumInterfaces) << std::endl;

        const libusb_interface* inter;
        const libusb_interface_descriptor* interdesc;
        const libusb_endpoint_descriptor* epdesc;

        for(int i=0 ; i<static_cast<int>(config->bNumInterfaces) ; ++i)
        {
            inter = &config->interface[i];
            std::cout << "\t\t-Number of alternate settings: " << inter->num_altsetting << std::endl;
            for(int j=0; j<inter->num_altsetting; ++j)
            {
                interdesc = &inter->altsetting[j];
                std::cout << "\t\t\tInterface Number: " <<  static_cast<int>(interdesc->bInterfaceNumber) << " | ";
                std::cout << "Number of endpoints: " <<  static_cast<int>(interdesc->bNumEndpoints) << std::endl;
                for(int k=0; k<static_cast<int>(interdesc->bNumEndpoints); ++k)
                {
                    epdesc = &interdesc->endpoint[k];
                    std::cout << "\t\t\t\tDescriptor Type: " <<  static_cast<int>(epdesc->bDescriptorType) << " | ";
                    std::cout << "EP Address: " <<  static_cast<int>(epdesc->bEndpointAddress) << std::endl;
                }
            }
        }

        libusb_free_config_descriptor(config);
    }
    else
    {
        std::cout << "\tNo descriptor found" << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main()
{
    libusb_device**  devs;
    libusb_context* ctx = nullptr;
    ssize_t deviceNumber;

    //initialize a library session
    int error = libusb_init(&ctx);
    if(error < 0)
    {
        std::cerr << "Init Error " << error << std::endl;
        return EXIT_FAILURE;
    }

    //set verbosity level to 3, as suggested in the documentation
    libusb_set_debug(ctx, 3);

    deviceNumber = libusb_get_device_list(ctx, &devs);
    if(deviceNumber < 0)
    {
        std::cerr << "Get Device Error" << std::endl;
    }

    std::cout << deviceNumber << " Devices in list." << std::endl;

    for(ssize_t i=0 ; i<deviceNumber ; ++i)
    {
        printdev(devs[i], i);
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);

    return EXIT_SUCCESS;
}
