#include <iostream>
#define __CL_ENABLE_EXCEPTION
#include <CL/cl.h>

int main()
{
    cl_uint platformNumber = 0;
    cl_platform_id platform_ids[8];
    clGetPlatformIDs(8, platform_ids, &platformNumber);

    char m_string[256];
    cl_device_type m_device_type;
    cl_uint m_value;
    size_t sizes[3];
    cl_ulong ul_value;
    for(int i = 0; i < platformNumber; ++i)
    {
        std::cout << "Platform idx : " << i << std::endl;
        cl_platform_id platform = platform_ids[i];
        clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 256, m_string, NULL);
        std::cout << "Platform vendor : " << m_string << std::endl;
        clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 256, m_string, NULL);
        std::cout << "Platform version : " << m_string << std::endl;

        cl_uint device_number = 0;
        cl_device_id device_ids[8];
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 8, device_ids, &device_number);
        for(int j = 0; j < device_number; ++j)
        {
            std::cout << "    device idx : " << j << std::endl;
            cl_device_id device = device_ids[j];
            clGetDeviceInfo(device, CL_DEVICE_NAME, 256, m_string, NULL);
            std::cout << "    device name : " << m_string << std::endl;
            clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &m_device_type, NULL);
            switch(m_device_type)
            {
                case CL_DEVICE_TYPE_CPU:
                    std::cout << "    device type : CPU" << std::endl;
                    break;
                case CL_DEVICE_TYPE_GPU:
                    std::cout << "    device type : GPU" << std::endl;
                    break;
                case CL_DEVICE_TYPE_ACCELERATOR:
                    std::cout << "    device type : ACCELERATOR" << std::endl;
            }
            clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), & m_value, NULL);
            std::cout << "    device max compute units : " << m_value << std::endl;
            clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * 3, sizes, NULL);
            std::cout << "    device max work item sizes : [" << sizes[0] << "][" << sizes[1] << "][" << sizes[2] << "]" << std::endl;
            clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_uint), &m_value, NULL);
            std::cout << "    device max work group size : "  << m_value << std::endl;
            clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &ul_value, NULL);
            std::cout << "    device max mem alloc size : " << ul_value << std::endl;
            clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), &ul_value, NULL);
            std::cout << "    device max constant buffer size : " << ul_value << std::endl;
        }
    }
    return 0;
}