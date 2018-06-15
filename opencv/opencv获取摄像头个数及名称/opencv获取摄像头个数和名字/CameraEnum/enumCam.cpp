#include<iostream>
#include "strmif.h"
#include <initguid.h>
#include<vector>
#include<string>
#include "windows.h"
#include "tchar.h"
#include <setupapi.h>
#include <functional>
#include <map>
#pragma comment(lib, "setupapi.lib")

using namespace std;

#define VI_MAX_CAMERAS  20

DEFINE_GUID(CLSID_SystemDeviceEnum, 0x62be5d10, 0x60eb, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(CLSID_VideoInputDeviceCategory, 0x860bb310, 0x5d01, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(IID_ICreateDevEnum, 0x29840822, 0x5b84, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);



//char deviceNames[VI_MAX_CAMERAS][255];



int listDevices(vector<string>& list){

	//COM Library Intialization
	//comInit();

	//if (!silent)printf("\nVIDEOINPUT SPY MODE!\n\n");


	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	int deviceCounter = 0;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
		reinterpret_cast<void**>(&pDevEnum));


	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the video capture category.
		hr = pDevEnum->CreateClassEnumerator(
			CLSID_VideoInputDeviceCategory,
			&pEnum, 0);

		if (hr == S_OK){

			//if (!silent)printf("SETUP: Looking For Capture Devices\n");
			IMoniker *pMoniker = NULL;

			while (pEnum->Next(1, &pMoniker, NULL) == S_OK){

				IPropertyBag *pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void**)(&pPropBag));

				if (FAILED(hr)){
					pMoniker->Release();
					continue;  // Skip this one, maybe the next one will work.
				}


				// Find the description or friendly name.
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"Description", &varName, 0);

				if (FAILED(hr)) hr = pPropBag->Read(L"FriendlyName", &varName, 0);

				if (SUCCEEDED(hr)){

					hr = pPropBag->Read(L"FriendlyName", &varName, 0);

					int count = 0;
					char tmp[255] = {0};
					//int maxLen = sizeof(deviceNames[0]) / sizeof(deviceNames[0][0]) - 2;
					while (varName.bstrVal[count] != 0x00 && count < 255) {
						tmp[count] = (char)varName.bstrVal[count];
						count++;
					}
					list.push_back(tmp);
					//deviceNames[deviceCounter][count] = 0;

					//if (!silent)printf("SETUP: %i) %s \n", deviceCounter, deviceNames[deviceCounter]);
				}

				pPropBag->Release();
				pPropBag = NULL;

				pMoniker->Release();
				pMoniker = NULL;

				deviceCounter++;
			}

			pDevEnum->Release();
			pDevEnum = NULL;

			pEnum->Release();
			pEnum = NULL;
		}

		//if (!silent)printf("SETUP: %i Device(s) found\n\n", deviceCounter);
	}

	//comUnInit();

	return deviceCounter;
}


int imageDeviceEnum(vector<string>& cameraName)
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;
	int num = 0;

	// 得到所有设备 HDEVINFO      
	hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (hDevInfo == INVALID_HANDLE_VALUE)
		return 0;

	// 循环列举     
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		char szClassBuf[MAX_PATH] = { 0 };
		char szDescBuf[MAX_PATH] = { 0 };

		// 获取类名  
		if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS, NULL, (PBYTE)szClassBuf, MAX_PATH - 1, NULL))
			continue;

		//获取设备描述信息
		//if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)szDescBuf, MAX_PATH - 1, NULL))
		//continue;
		if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)szDescBuf, MAX_PATH - 1, NULL))
			continue;

		string str(szClassBuf);
		string str2(szDescBuf);

		if (str == "Image")
		{
			num++;
			cameraName.push_back(str2);
		}
	}

	//  释放     
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return num;
}
int serialEnum(vector<string>& serialName, vector<string>& serialPortName)
{
	int i = 0;//串口个数
	CHAR Name[25];
	UCHAR szPortName[25];
	LONG Status;
	DWORD dwIndex = 0;
	DWORD dwName;
	DWORD dwSizeofPortName;
	DWORD Type;
	HKEY hKey;
	//CString   strSerialList[256];  // 临时定义 256 个字符串组，因为系统最多也就 256 个 
	//CString   strSerialList[256];  // 临时定义 256 个字符串组，因为系统最多也就 256 个 
	string strSerialName;
	string strSerialPort;

	LPCTSTR data_Set = "HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	dwName = sizeof(Name);
	dwSizeofPortName = sizeof(szPortName);
	//long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey)); 
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey); //打开一个制定的注册表键,成功返回ERROR_SUCCESS即“0”值
	if (ret0 == ERROR_SUCCESS)
	{
		do
		{

			Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type, szPortName, &dwSizeofPortName);//读取键值 
			if ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA))
			{
				strSerialName = string(Name);
				strSerialPort = string((CHAR*)szPortName);
				serialName.push_back(strSerialName);
				serialPortName.push_back(strSerialPort);

				i++;// 串口计数 
			}
			//每读取一次dwName和dwSizeofPortName都会被修改 
			//注意一定要重置,否则会出现很离奇的错误,
			dwName = sizeof(Name);
			dwSizeofPortName = sizeof(szPortName);
		} while ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA));

		RegCloseKey(hKey);
	}
	return i;
}

int serialEnum(map<string,string>& serialNames)
{
	int i = 0;//串口个数
	CHAR Name[25];
	UCHAR szPortName[25];
	LONG Status;
	DWORD dwIndex = 0;
	DWORD dwName;
	DWORD dwSizeofPortName;
	DWORD Type;
	HKEY hKey;
	//CString   strSerialList[256];  // 临时定义 256 个字符串组，因为系统最多也就 256 个 
	//CString   strSerialList[256];  // 临时定义 256 个字符串组，因为系统最多也就 256 个 
	string strSerialName;
	string strSerialPort;

	LPCTSTR data_Set = "HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	dwName = sizeof(Name);
	dwSizeofPortName = sizeof(szPortName);
	//long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey)); 
	long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey); //打开一个制定的注册表键,成功返回ERROR_SUCCESS即“0”值
	if (ret0 == ERROR_SUCCESS)
	{
		do
		{

			Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type, szPortName, &dwSizeofPortName);//读取键值 
			if ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA))
			{
				strSerialName = string(Name);
				strSerialPort = string((CHAR*)szPortName);
				//serialName.push_back(strSerialName);
				//serialPortName.push_back(strSerialPort);
				serialNames.insert(pair<string, string>(strSerialName, strSerialPort));
				i++;// 串口计数 
			}
			//每读取一次dwName和dwSizeofPortName都会被修改 
			//注意一定要重置,否则会出现很离奇的错误,
			dwName = sizeof(Name);
			dwSizeofPortName = sizeof(szPortName);
		} while ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA));

		RegCloseKey(hKey);
	}
	return i;
}

int main()
{
	vector<string> CameraName; 
	//vector<string> serialName;
	//vector<string> serialPortName;
	map<string, string> serialNames;
	//deviceNames[VI_MAX_CAMERAS][255] = { 0 };
	int num = listDevices(CameraName);
	cout << "摄像头个数：" << num << endl;
	for (int i = 0; i < num;i++){
		cout << i << ":" << CameraName[i] << endl;
	}
	int snum = serialEnum(serialNames);
	map<string, string>::iterator iter = serialNames.begin();
	cout << endl;
	while (iter != serialNames.end()){
		cout << iter->first << " : " << iter->second<<endl;
		iter++;
	}


	string v1 = "XI100DUSB-SDI Video";
	string v2 = "Logitech HD Webcam C270";
	string com = "\\Device\\VCP0";

	cout << endl;

	for (int i = 0; i < CameraName.size(); i++){
		if (CameraName[i] == v1){
			cout << v1 << " is " << i << endl;
		}
		else if (CameraName[i] == v2){
			cout << v2 << " is " << i << endl;
		}
	}
	vector<string>::iterator pos = find(CameraName.begin(), CameraName.end(), v1);
	cout <<*pos <<" 的编号为："<<distance(CameraName.begin(),pos);
	cout << endl;
	pos = find(CameraName.begin(), CameraName.end(), v2);
	cout << *pos << "的编号为：" << distance(CameraName.begin(), pos);
	cout << endl;
	cout << endl; cout << endl; cout << endl; cout << endl;
	map<string, string>::iterator siter = serialNames.find(com);
	if (siter != serialNames.end())
		//cout << com<< "端口为："<<siter->second << endl;
		system("pause");
}

