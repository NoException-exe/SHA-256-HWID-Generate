#include "hwid.hpp"
#include "../lib/picosha2.h"

DWORD Hwid::getTotalRam()
{
    MEMORYSTATUSEX mem{};
    mem.dwLength = sizeof(mem);
    if (GlobalMemoryStatusEx(&mem)) {
        return static_cast<DWORD>(mem.ullTotalPhys / (static_cast<unsigned long long>(1024) * 1024));
    }

    return 0;
}

std::string Hwid::getCpuName()
{
    char cpuModel[49] = { 0 };
    int cpuInfo[4] = { -1 };
    __cpuid(cpuInfo, 0x80000002);
    memcpy(cpuModel, cpuInfo, 16);
    __cpuid(cpuInfo, 0x80000003);
    memcpy(cpuModel + 16, cpuInfo, 16);
    __cpuid(cpuInfo, 0x80000004);
    memcpy(cpuModel + 32, cpuInfo, 16);
    return std::string(cpuModel);
}


std::vector<DISPLAY_DEVICE> Hwid::getDisplayDevices()
{
    std::vector<DISPLAY_DEVICE> devices;
    DISPLAY_DEVICE displayDevice = { 0 };
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    for (DWORD i = 0; EnumDisplayDevices(nullptr, i, &displayDevice, 0); i++) {
        devices.push_back(displayDevice);
    }
    return devices;
}



std::string Hwid::getGPU()
{
    std::vector<DISPLAY_DEVICE> devices = getDisplayDevices();
    for (const auto& device : devices) {
        if (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) {
        
            size_t convertedLength = mbstowcs(nullptr, device.DeviceString, 0) + 1;
            wchar_t* deviceString = new wchar_t[convertedLength];
            mbstowcs_s(nullptr, deviceString, convertedLength, device.DeviceString, _TRUNCATE);

            std::wstring wResult(deviceString);

            delete[] deviceString;

            std::string result(wResult.begin(), wResult.end());

            return result;
        }
    }
    return "";
}



std::string Hwid::getMACAddress()
{
    IP_ADAPTER_INFO AdapterInfo[16];
    DWORD dwBufLen = sizeof(AdapterInfo);
    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
    if (dwStatus != ERROR_SUCCESS) {
        return "";
    }

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    while (pAdapterInfo) {
        if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) {
            std::string macAddress;
            char buf[3];
            for (int i = 0; i < (int)pAdapterInfo->AddressLength; i++) {
                sprintf_s(buf, "%.2X", (int)pAdapterInfo->Address[i]);
                macAddress.append(buf);
                if (i < (int)pAdapterInfo->AddressLength - 1) {
                    macAddress.append(":");
                }
            }
            return macAddress;
        }
        pAdapterInfo = pAdapterInfo->Next;
    }
    return "";
}

std::string Hwid::getComputerName()
{
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    if (!GetComputerNameExA(ComputerNamePhysicalDnsHostname, computerName, &size)) {
        return "";
    }
    return computerName;
}


std::string Hwid::hwidHash() {
    std::string hash_text;
    std::string data = getComputerName() + getCpuName() + getGPU() + getMACAddress() + std::to_string(getTotalRam());
    picosha2::hash256_hex_string(data, hash_text);
    return hash_text;
}


void Hwid::pcInformation()
{
    std::cout << "Computer Name: " << getComputerName() << std::endl;
    std::cout << "Cpu Name: " << getCpuName() << std::endl;
    std::cout << "Gpu Name: " << getGPU() << std::endl;
    std::cout << "MAC Address: " << getMACAddress() << std::endl;
    std::cout << "Ram: " << std::to_string(getTotalRam()) << std::endl;
}