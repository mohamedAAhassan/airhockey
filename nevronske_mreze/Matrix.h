#ifndef __CMATRIX_H
#define __CMATRIX_H

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class CMatrix
{
private:
    vector< vector<T> > matrix ; //(m, vector<T>(n, 0));
    unsigned M, N;

public:
    CMatrix(unsigned m, unsigned n)
    {
        this->M = m;
        this->N = n;
        this->matrix.assign(m, vector<T>(n, 0));
    }


    CMatrix(unsigned m, unsigned n, T initValue)
    {
        this->M = m;
        this->N = n;
        this->matrix.assign(m, vector<T>(n, initValue));
    }

    CMatrix()
    {
        this->M = this->N = 0;
    }

    T at(unsigned i, unsigned j)
    {
        if(i<M && j<N)
                return matrix[i][j];
        else
                return NULL;
    }

    bool insert(T element, unsigned i, unsigned j)
    {
        if(i<M && j<N)
        {
                matrix[i][j] = element;
                return true;
        }
        else
                return false;
    }

    vector<T>* returnVectorPtr(int i)
    {
        return &matrix[i];
    }

    vector<T> returnVector(int i)
    {
        return matrix[i];
    }

    unsigned getM() const
    {
        return this->M;
    }

    unsigned getN() const
    {
        return this->N;
    }

    void addRows(unsigned numRows) // vrstica
    {
        for(unsigned i=0; i<numRows; i++)
        {
                matrix.push_back(vector<T>(this->N, 0));
                this->M ++;
        }
    }

    void addColumns(unsigned numColumns) // stolpec
    {
        for(unsigned i=0; i<numColumns; i++)
        {
                for(unsigned i=0; i<matrix.size(); matrix[i++].push_back(0));
                this->N ++;
        }
    }

    void addRows(T initValue, unsigned numRows)
    {
        for(unsigned i=0; i<numRows; i++)
        {
                matrix.push_back(vector<T>(this->N, initValue));
                this->M ++;
        }
    }

    void addColumns(T initValue, unsigned numColumns)
    {
        for(unsigned i=0; i<numColumns; i++)
        {
                for(unsigned i=0; i<matrix.size(); matrix[i++].push_back(initValue));
                this->N ++;
        }
    }

    void print()
    {
        for(unsigned i=0; i<this->M; i++)
        {
                for(unsigned j=0; j<this->N; j++)
                cout<<this->matrix[i][j]<<' ';
                cout<<endl;
        }
    }
};

#endif
