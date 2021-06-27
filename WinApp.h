#pragma once
#include <windows.h>

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using Microsoft::WRL::ComPtr;

namespace ResWolf
{
	class WinApp
	{
	public:
		WinApp();
		~WinApp();
		void init();
		LRESULT msgPrc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
		//getters/setters
		HWND getMainWindow();
		int getClientWidth();
		int getClientHeight();

	private:
		/* ----- windows ----- */
		bool initMainWindow();
		
		HINSTANCE mainAppInstance;
		HWND mainWindow;
		
		int clientWidth = 1024;
		int clientHeight = 768;

		void onResize();

		/* ----- d3d ----- */

		bool initDirect3D();
		void createCommandObjects();
		void createSwapChain();
		void createRtvDsvDescriptorHeaps();

		void flushCommandQueue();

		// Command stuff
		ComPtr<ID3D12CommandQueue> commandQueue;
		ComPtr<ID3D12CommandAllocator> directCommandListAllocator;
		ComPtr<ID3D12GraphicsCommandList> commandList;

		// Hardware render stuff
		ComPtr<IDXGIFactory4> dxgiFactory;
		ComPtr<ID3D12Device> d3dDevice;
		ComPtr<ID3D12Fence> fence;
		UINT64 currentFence = 0;

		// Heaps
		ComPtr<ID3D12DescriptorHeap> rtvHeap;
		ComPtr<ID3D12DescriptorHeap> dsvHeap;

		static const int swapChainBufferCount = 2;
		int currentBackBuffer = 0;
		ComPtr<ID3D12Resource> swapChainBuffer[swapChainBufferCount];
		ComPtr<IDXGISwapChain> swapChain;
		ComPtr<ID3D12Resource> depthStencilBuffer;

		UINT rtvDescriptorSize = 0;
		UINT dsvDescriptorSize = 0;
		UINT cbvSrvUavDescriptorSize = 0;

		DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

		D3D12_VIEWPORT screenViewport;
		D3D12_RECT scissorRect;

		UINT msaa4xQuality = 0;
		bool msaa4xState = false;
	};

	LRESULT CALLBACK MainWndProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
	);
}