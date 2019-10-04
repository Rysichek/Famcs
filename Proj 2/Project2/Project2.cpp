// Project2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project2.h"
#include "Stack,Iterator.h"
#include "Visitor.h"
#include"String.h"
#include<vector>

BOOL CALLBACK dlgHandler(HWND, UINT, WPARAM, LPARAM);

Model* model = new Model();

		
class View
{
private:	

	Model* model;
	string data;
	vector<int> vect_data;
	HWND hModel;
	HWND hD;
public:
	View(HWND hM, Model *m, HWND hDD)
	{
		model = m;
		hD = hDD;
		hModel = hM;
	}

	void UpdateDialog()
	{
		SendMessageA(hModel, LB_RESETCONTENT, NULL, NULL);
		data = model->toString();
		toVector();
		for (int i = 0;i < vect_data.size();i++) {
			char buff[100];
			sprintf_s(buff, 100, "%d", vect_data[i]);
			SendMessageA(hModel, LB_ADDSTRING, NULL, (LPARAM)buff);
		}

	}
	void toVector()
	{
		int numb = 0;
		for (int j = 0;j < data.size();j++)
		{
			while (data[j] != ' ')
			{
				numb = (numb + data[j]) * 10;
				j++;
			}
			vect_data.push_back(numb / 10);
			numb = 0;

		}
	}

	HWND get_hD()
	{
		return hD;
	}
	void close()
	{
		DestroyWindow(hD);
	}
	void destroy()
	{
		PostQuitMessage(0);
	}
	void push_view(int value)
	{
		char buff[100];
		sprintf_s(buff, 100, "%d happily pushed", value);
		SetDlgItemText(hD, IDC_OUTPUT, buff);
	}
	void pop_view(bool ind)
	{
		if (ind == true)
		{
			SetDlgItemText(hD, IDC_OUTPUT, "Mistake, model is empty!");
		}
		else
		{
			char buff[100];
			sprintf_s(buff, 100, "%d happily popped", model->top());
			SetDlgItemText(hD, IDC_OUTPUT, buff);
		}
	}
	void clear_view()
	{
		SetDlgItemText(hD, IDC_OUTPUT, "Your cleaned model");
	}
	void is_EmptyView(bool ind)
	{
		if (ind == true)
		{
			SetDlgItemText(hD, IDC_OUTPUT, "model is empty!");
	     }
		else
		{
			SetDlgItemText(hD, IDC_OUTPUT, "No, model isn't empty!");
		}

	}
	void visitor_view(bool ind,int value)
	{
		if (ind == true)
		{
			SetDlgItemText(hD, IDC_OUTPUT, "Mistake, model is empty!");
		}
		else
		{
			char buff[100];
			sprintf_s(buff, 100, "%d Maximum in the model", value);
			SetDlgItemText(hD, IDC_OUTPUT, buff);

		}
	}
	void top_view(bool ind)
	{
		if (ind == true)
		{
			SetDlgItemText(hD, IDC_OUTPUT, "Mistake, model is empty!");
		}
		else
		{
			if (!model->IsEmpty())
			{
				char buff[100];
				sprintf_s(buff, 100, "%d happily topped", model->top());
				SetDlgItemText(hD, IDC_OUTPUT, buff);
			}
	
		}
	}
};

class Controller
{
private:
	Model* model;
	View* view;
public:
	Controller(Model* _model, View* _view)
	{
		model = _model;
		view = _view;
	}
	void endDialog(int wParam)
	{
		EndDialog(view->get_hD(), wParam);
	}
	void close()
	{
		view->close();
	}
	void destroy()
	{
		view->destroy();
	}
	void push()
	{
		int toAdd = GetDlgItemInt(view->get_hD(), IDC_INPUT, NULL, TRUE);
		model->push(toAdd);
		view->UpdateDialog();
		view->push_view(toAdd);
	}
	void pop()
	{
		if (model->IsEmpty() != 1) {
			model->pop();	
		}
		view->pop_view(model->IsEmpty());
		view->UpdateDialog();
	}
	void clear()
	{
		model->Clear();
		view->UpdateDialog();
		view->clear_view();
	}
	void is_Empty()
	{
		view->is_EmptyView(model->IsEmpty());
	}
	void visitor()
	{
		GetMax_Numb q;
		model->accept(q);
		view->visitor_view(model->IsEmpty(),q.GetNumb());
	}
	void top()
	{
		view->top_view(model->IsEmpty());
	}

};




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, dlgHandler);
	return 0;
}

INT_PTR _stdcall CALLBACK dlgHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	View *view = new View(GetDlgItem(hDlg, IDC_LIST1),model,hDlg);
	Controller* controller = new Controller(model, view);

	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG: {
		return (INT_PTR)TRUE;
	}

	case WM_CLOSE: {
		controller->close();
		break;
	}

	case WM_DESTROY: {
		controller->destroy();
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_EXIT: {
			controller->endDialog(LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_BUTTON_PUSH: {
			controller->push();	
			break;
		}

		case IDC_BUTTON_POP: {
			controller->pop();
			break;
		}
		case IDC_BUTTON_CLEAR: {
			controller->clear();
			break;
		}
		case IDC_BUTTON_EMPTY: {
			controller->is_Empty();
			break;
		}


	  case IDC_BUTTON_VISITOR: {
		  controller->visitor();
	   break;
   }

		case IDC_BUTTON_TOP: {
			controller->top();
			break;
			}

		}
		break;
	}
	return (INT_PTR)FALSE;
}


