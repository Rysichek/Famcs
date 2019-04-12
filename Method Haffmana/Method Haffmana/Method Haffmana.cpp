// Method Haffmana.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "pch.h"
#include <iostream>
#include <queue>
#include <bitset>
#include <fstream>
#include <vector>
using namespace std;


ofstream code("code.txt");
ofstream key;
ofstream out1("out.bin");
ofstream out2("out.txt",ios::binary);
ifstream in("input.txt");
ifstream in2("input.txt");
ifstream out("out.txt");
ofstream numb("number.txt");

class pnode {
public:
	char ch;
	pnode *ptr_null, *ptr_one;
	pnode(char &c, pnode *p_n, pnode * p_o)
	{
		ch = c;
		ptr_null = p_n;
		ptr_one = p_o;
	}
	pnode(char c, pnode *p_n, pnode * p_o)
	{
		ch = c;
		ptr_null = p_n;
		ptr_one=p_o;
	}
};
class que_elm {
public:
	int sum;
	pnode * elm;
	que_elm(int & sm, pnode *el)
	{
		sum = sm; 
		elm=el;
	}
	que_elm(int & sm, pnode &el) 
	{
		sum = sm;
		elm = &el; 
	}
	que_elm()
	{
		sum = 0;
		elm=0;
	}
	que_elm(const que_elm & el)
	{
		sum = el.sum; 
		elm = el.elm;
	}
};
struct Compare {
	bool operator()(que_elm &  lft, que_elm & rght) {
		return lft.sum > rght.sum;
	}
};

class m_el {
public: bool bl[8];
		int count;
};

void dfs(pnode * node, vector<bool> &dfs_vec, m_el * m_bool) {
	if (node->ptr_null != 0 && node->ptr_one != 0) {
		dfs_vec.push_back(false);
		dfs(node->ptr_null, dfs_vec, m_bool);
		dfs_vec.pop_back();
		dfs_vec.push_back(true);
		dfs(node->ptr_one, dfs_vec, m_bool);
		dfs_vec.pop_back();
	}
	else {
		m_bool[(int)node->ch].count = dfs_vec.size();

		for (int i = 0; i < dfs_vec.size(); i++) {
			m_bool[(int)node->ch].bl[i] = dfs_vec[i];
		}
    }
};

void bfs(queue <pnode> que_bfs, pnode *root, int i_node)
{
	que_bfs.push(*root);
	while (!que_bfs.empty()) {
		*root = que_bfs.front();
		que_bfs.pop();
		if (root->ptr_null->ptr_null != 0 && root->ptr_null->ptr_one != 0) {
			   que_bfs.push(*root->ptr_null);
			key << (char)i_node;
		}
		else {
			key << root->ptr_null->ch;
		}
		if (root->ptr_one->ptr_one != nullptr && root->ptr_one->ptr_null != 0) {
				que_bfs.push(*root->ptr_one);
			key << (char)i_node;
		}
		else { key << root->ptr_one->ch; }
	}
};




int main() {
	key.open("key.txt");
	int tempsum;
	bitset<8> bt_st;
	int mpeh[256], i_node = -1;
	m_el m_bool[256];
	for (int i = 0; i < 256; i++)
	{
		m_bool[i].count = 0;
	}
	int  dfs_cnt = 0;
	int cnt = 0;
	char ch;
	vector<bool> dfs_vec;
	queue <pnode> que_bfs;
	priority_queue<que_elm, vector<que_elm>, Compare> que_pnode;
	que_elm tmp1_elm, tmp2_elm;
	pnode *root;
	for (int i = 0; i < 256; i++) {
		mpeh[i] = 0;
	}

	int number = 0;
	while (in.get(ch)) { mpeh[(int)ch]++;
	number++;
	}
	numb << number;
	in.close();

	for (int i = 0; i < 256; i++) {
		if (mpeh[i] != 0) code << (char)i << " - " << mpeh[i] << endl;
	}

	for (int i = 0; i < 256; i++) {
		if (mpeh[i] != 0)que_pnode.push(que_elm(mpeh[i], new pnode((char)i, nullptr, nullptr)));
	}

	while (que_pnode.size() > 2) {
		tmp1_elm = que_pnode.top();
		que_pnode.pop();
		tmp2_elm = que_pnode.top();
		que_pnode.pop();
		tempsum = tmp1_elm.sum + tmp2_elm.sum;
		que_pnode.push(que_elm(tempsum, new pnode((char)0, tmp1_elm.elm, tmp2_elm.elm)));
	}

	tmp1_elm = que_pnode.top();
	que_pnode.pop();
	tmp2_elm = que_pnode.top();
	que_pnode.pop();

	root = new pnode((char)0, tmp1_elm.elm, tmp2_elm.elm);

	dfs(root, dfs_vec, m_bool);



	for (int i = 0; i < 256; i++)
	{
		if (m_bool[i].count != 0)
		{
			cout << (char)i << " ";
			key << (char)i << " ";
			for (int j = 0; j < m_bool[i].count; j++)
			{

				cout << m_bool[i].bl[j];
				key<< m_bool[i].bl[j];

			}
			key << endl;
			cout << " ";
		}
	}

	cout << endl;

	int k=0;
	while (in2.get(ch)) {
		for (int i = 0; i < m_bool[(int)ch].count; i++)
		{
			bt_st[7 - cnt] = m_bool[(int)ch].bl[i];
			cnt++;
			if (cnt == 8)
			{
				cnt = 0;
				for (int i = 0; i < 8; i++)
				{
					cout << bt_st[i];
				}
				out1 << (char)bt_st.to_ulong();
				out2 << (char)bt_st.to_ulong();
				cout << " ";
				cout << (char)bt_st.to_ulong();
				cout << endl;
			}
		}
	}

	if (cnt != 0)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << bt_st[i];
		}
		out1 << (char)bt_st.to_ulong();
		out2 << (char)bt_st.to_ulong();
		cout << " ";
		cout << (char)bt_st.to_ulong();
		cout << endl;
	}

	key.close();
	

}