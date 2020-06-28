#include "mex.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning (disable : 4146)

#import "C:\Program Files\Prior Scientific\Prior Software\Prior.dll" no_namespace named_guids

using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	/*------------------------------------------------------------------
	| Parameters from matlab that will determine which function to run |
	-------------------------------------------------------------------*/
	int func_num = mxGetScalar(prhs[0]);

	/*------------------------------------------------------------------------------------------------------------------------------------
	| Both x and y will be the two main parameters. If a function requiring only one parameter is called, x will serve as that parameter |
	-------------------------------------------------------------------------------------------------------------------------------------*/
	double x, y;
	if (nlhs >= 3)
	{
		x = mxGetScalar(prhs[1]);
		y = mxGetScalar(prhs[2]);
	}
	else if (nlhs == 2)
	{
		x = mxGetScalar(prhs[1]);
	}



	/*-----------
	| Main Code |
	------------*/

	long port = 1;
	HRESULT hRes;



	long busy;

	::CoInitialize(NULL);
	{
		IScanPtr pScan;
		IStagePtr pStage;

		hRes = pScan.CreateInstance(__uuidof(Scan));
		if (FAILED(hRes))
		{
			printf("IScanPtr::CreateInstance failed w/err 0x%08lx\n", hRes);
		}
		else
		{
			long result = pScan->Connect(&port);

			if (result)
			{
				printf("Failed to connect to controller %d\n", result);
			}
			else
			{
				printf("%d\n", pScan->GetControllerFirmwareVersion());

				hRes = pStage.CreateInstance(__uuidof(Stage));
				if (FAILED(hRes))
				{
					//printf("IStagePtr::CreateInstance failed w/err 0x%08lx\n", hRes);
				}
				else
				{
					/*---------------------
					| Call functions here |
					----------------------*/
					switch (func_num)
					{
						case 1:
							pStage->GetPosition(&x, &y);
                            				mexPrintf("(%d , %d)\n", x, y);
							break;
						case 2:
							pStage->MoveAtVelocity(x, y);
							break;
						case 3:
							pStage->MoveBack(x);
							break;
						case 4:
							pStage->MoveForward(x);
							break;
						case 5:
							pStage->MoveLeft(x);
							break;
						case 6:
							pStage->MoveRelative(x, y);
							break;
						case 7:
							pStage->MoveRight(x);
							break;
						case 8:
							pStage->MoveToAbsolute(x, y);
							break;
						case 9:
							pStage->MoveXAtVelocityUntilEncoderReference(x);
							break;
						case 10:
							pStage->MoveXToAbsolute(x);
							break;
						case 11:
							pStage->MoveYAtVelocityUntilEncoderReference(x);
							break;
						case 12:
							pStage->MoveYToAbsolute(x);
							break;
						case 13:
							pStage->RestoreReference();
							break;
						case 14:
							pStage->SetPosition(x, y);
							break;
						case 15:
							pStage->SetReference();
							break;
						case 16:
							pStage->SkewAbout();
							break;
						case 17:
							pStage->SkewSecond();
							break;
						default:
							cout << "No function was called" << endl;
							break;
					}

					do
					{
						pScan->IsMoving(&busy);
					} while (busy & 0x03);

					do
					{
						pScan->IsMoving(&busy);
					} while (busy & 0x03);

					pStage->GetPosition(&x, &y);

					pScan->DisConnect();
				}
			}
		}
	}

	::CoUninitialize();

	return;
}
