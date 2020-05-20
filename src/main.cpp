#include <iostream>
#include <libusb-1.0/libusb.h>
#include <thread>
#include <chrono>

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

        std::uint8_t portNumber =  libusb_get_port_number(_dev);
        std::cout << "\t\t-Port number: " << static_cast< int >(portNumber) << std::endl;

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

int hotplug_callback(struct libusb_context*, struct libusb_device* _dev, libusb_hotplug_event _event, void*)
{
    static libusb_device_handle *handle = nullptr;
    struct libusb_device_descriptor desc;
    (void)libusb_get_device_descriptor(_dev, &desc);

    if(_event == LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED)
    {
        int error = libusb_open(_dev, &handle);
        if(error != LIBUSB_SUCCESS)
        {
            std::cout << "Could not open USB device" << std::endl;
        }
    }
    else if(_event == LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT)
    {
        if(handle)
        {
            libusb_close(handle);
            handle = nullptr;
        }
    }
    else
    {
        std::cout << "Unhandled event " << _event << std::endl;
    }

    return 0;
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

    // Display device interfaces
    for(ssize_t i=0 ; i<deviceNumber ; ++i)
    {
        printdev(devs[i], i);
    }

    // Test to check hotplug
    {
        if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
        {
            std::cout << "Hotplug capabilites are not supported on this platform" << std::endl;
        }
        else
        {
            libusb_hotplug_callback_handle handle;
            int error = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, LIBUSB_HOTPLUG_NO_FLAGS , 0x1532, 0x46, LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback, nullptr, &handle);

            if(error != LIBUSB_SUCCESS)
            {
                std::cout << "Error creating a hotplug callback: " << error << std::endl;
            }
            else
            {
                while(true)
                {
                    libusb_handle_events_completed(nullptr, nullptr);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);

    return EXIT_SUCCESS;
}
