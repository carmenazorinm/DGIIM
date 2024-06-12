/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>

using namespace std;

double v_npos = Matrix::npos;
const double c_npos = Matrix::npos;

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    for(int i =0; i < nrows; i++)
        for(int j = 0; j < ncols; j++)
            dest[i][j] = org[i][j];
}

/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    double ** block = new double*[r];
    for(int i = 0; i < r; i++)
        block[i] = new double [c];
    // allocate memory into block
    return block;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool found = false;
    for (int i = 0; i < idx.size() && !found; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            found = true;
        }
    }
    return salida;
}

void Matrix::deallocate() {
    if (_data != nullptr){
        for(int i = 0; i < _nrows; i++)
            delete[] _data[i];
    }
    
    delete[] _data;
    _data = nullptr;
    _nrows = 0;
    _ncols = 0;
}


Matrix::Matrix() {
    _nrows = 0;
    _ncols = 0;
    _data = nullptr;
}

void Matrix::setValues(double valor) {
    
    for(int row=0; row<_nrows; row++){
        for(int col=0; col<_ncols; col++){
            //_data[row][col]=valor;
            (*this)(row,col)=valor;
        }
    }
     
}



Matrix::Matrix(size_t f, size_t c, double vdef) {
    _nrows = f;
    _ncols = c;
    _data = allocate(f, c);
    setValues(vdef);
    
//    for(int i = 0; i < _nrows; i++)
//        for(int j = 0; j < _ncols; j++)
//            _data[i][j] = vdef;

}

Matrix::Matrix(const Matrix& orig) {
    _data = nullptr;
    deallocate();
    _data = allocate(orig._nrows, orig._ncols);
    _nrows = orig.rows();
    _ncols = orig.columns();
    
    _rowLabels = orig._rowLabels; //no sé si está bien
    _colLabels = orig._colLabels; //no sé si está bien
    
    copy(_data, orig._data, _nrows, _ncols);
    
    
}

Matrix::Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double value) {
    //NO COMPROBADO poner en el próximo error que me de de este método?
   
//    if(nrows >=1 && ncols >= 1){
//        Matrix(nrows,ncols,value);
//        for(int i =0;i<ncols;i++){
//            _colLabels.at(i).set(colsLabels[i],i);
//        }
//        for(int i =0; i < nrows;i++){
//            _rowLabels.at(i).set(rowLabels[i],i);
//        }
//    }     
//    else{
//        Matrix();
//    }
//    if(nrows <= 0 || ncols <=0){
//        Matrix();
//    }else{
//        Matrix(nrows,ncols,value);
//        for(int i =0;i<_ncols;i++){
//            _colLabels.at(i).set(colsLabels[i],i);
//        }
//        for(int i =0; i < _nrows;i++){
//            _rowLabels.at(i).set(rowLabels[i],i);
//        }
//    }
    
    if(nrows <= 0|| ncols <= 0)
        clear();
    else{
        _data = allocate(nrows, ncols);
        _nrows = nrows;
        _ncols = ncols;
        
        for(int row=0; row<_nrows; row++)
        for(int col=0; col<_ncols; col++)
            //_data[row][col]=value;
            (*this)(row,col)=value;

        setLabels(_rowLabels, rowLabels, nrows);
        setLabels(_colLabels, colsLabels, ncols);
    }
    
}



std::string Matrix::labelAtRow(size_t row) const { //HECHO POR LUIS 
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const { //HECHO POR LUIS
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double value) {
    
    deallocate();
    _nrows=nrows;
    _ncols=ncols;
    _data = allocate(_nrows, _ncols); //el allocate tiene que estar aquí debajo, si no, segmentation fault    
    setValues(value);
    
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    //NO COMPROBADO NI DE COÑA
    resize(nrows,ncols,value);
    
    if(!setLabels(_rowLabels, rowLabels, nrows) || !setLabels(_colLabels, colLabels, ncols))
        clear();
}

void Matrix::clear() {
    deallocate();
    _nrows=0;
    _ncols=0;
    _rowLabels.clear();
    _colLabels.clear();
}

Matrix::~Matrix() { //siempre es así
    deallocate();
}

double & Matrix::at(size_t f, size_t c) { //se puede cambiar poniendo ||
    
    bool fila_correcta = (0 <= f && f < _nrows);
    bool col_correcta = (0 <= c && c < _ncols);
    
    if (fila_correcta && col_correcta)
        return _data[f][c];
    else
        return v_npos;
}

const double & Matrix::at(size_t f, size_t c) const {
    
    bool fila_correcta = (0 <= f && f < _nrows);
    bool col_correcta = (0 <= c && c < _ncols);
    
    if (fila_correcta && col_correcta)
        return _data[f][c];
    else
        return v_npos;
}

double & Matrix::operator()(size_t f, size_t c) {
    return at(f,c); //justo el método de arriba
   
}

const double & Matrix::operator()(size_t f, size_t c) const {
    return at(f,c);
}

int Matrix::rowIndexOf(const std::string & label) const {
    
    int lower = _rowLabels.lower_bound(label);
    int upper = _rowLabels.upper_bound(label);
    
    if(lower == upper)
        return c_npos;
    else
        return _rowLabels.at(lower).getPos();
    
//    bool found = false;
//    int fila_buscada = v_npos;
//    for(int row=0; row<_nrows && !found; row++){
//        if(labelAtRow(row) == label){
//           found = true; 
//           fila_buscada = row;
//        } 
//    }
//    
//    return fila_buscada;
}

int Matrix::colIndexOf(const std::string & label) const {
    
    int lower = _colLabels.lower_bound(label);
    int upper = _colLabels.upper_bound(label);
    
    
    if(lower == upper)
        return c_npos;
    else
        return _colLabels.at(lower).getPos();
    
    
//    bool found = false;
//    int col_buscada = v_npos;
//    for(int col=0; col<_nrows && !found; col++){
//        if(labelAtCol(col) == label){
//           found = true; 
//           col_buscada = col;
//        } 
//    }
//    
//    return col_buscada;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
    int row = rowIndexOf(rowLabel); 
    int col = colIndexOf(colLabel);
    
    return at(row,col); //Del anterior at 
        
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
//    int row = rowIndexOf(rowLabel);
//    int col = colIndexOf(colLabel);
//    
//    return at(row,col);
    return at(rowLabel,colLabel);
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {
    int row = rowIndexOf(rowLabel);
    int col = colIndexOf(colLabel);
    
    return at(row,col);
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
//    int row = rowIndexOf(rowLabel);
//    int col = colIndexOf(colLabel);
//    
//    return at(row,col);
    return at(rowLabel,colLabel);
}

ostream & operator<<(ostream & flujo, const Matrix& m) {
    
    flujo << m._nrows << " " << m._ncols << endl;
    
    for(int i =0; i < m._nrows; i++)
        flujo << m.labelAtRow(i) << " ";
    
    flujo << endl;
    
    for (int i = 0; i < m._ncols; i++)
        flujo << m.labelAtCol(i) << " ";
    
    flujo << endl;
    
    for(int i = 0; i < m._nrows; i++){
        for(int j = 0; j < m._ncols; j++)
            flujo << m.at(i,j) << " ";
        flujo << endl;
    }
    
    return flujo;
    
    
}

Matrix & Matrix::operator=(const Matrix& m) { //Repasar
    if(&m != this){
        clear();
        _data =allocate(m._nrows, m._ncols );
        _nrows=m._nrows;
        _ncols=m._ncols;
        copy(_data, m._data , m._nrows, m._ncols);
        _rowLabels=m._rowLabels;
        _colLabels=m._colLabels;
                
    }
    return (*this);
}

//cambiar void a bool y return bool correct;
bool Matrix::setLabels(Index & idx, const string * labels, int nlabels){ //HECHO POR LUIS
    idx.clear();
    int lb,ub;
    bool correct = true;
    for (int i=0; i< nlabels && correct; i++){
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb==ub) { // it is NOT in the set
            idx.add(Pair(labels[i],i));
        } else {
            correct = false;
         }
    }
    if (!correct) idx.clear();
    
    return correct;
 }

int Matrix::getLabels(const Index & idx, string * labels) const {
    
    int contador = 0;
    
    while(contador < idx.size() && idx.size() > 0){
        labels[contador] = idx.at(contador).getKey();
        contador++;
    }
    
    //a lo mejor debería return idx.size(); por si idx.size() < 0, pero not sure
    return contador; 
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels,labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels,labels);
}

size_t Matrix::columns() const {
    return _ncols;
}

size_t Matrix::rows() const {
    return _nrows;
}

//uncomment
void Matrix::save(const string & nf) const{ //HECHO POR LUIS
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix "; 
        if (_rowLabels.size()==0)
            fsal << "unlabeled"<< endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" <<endl;
}

void Matrix::load(const string & nf) { //HECHO POR LUIS
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
         fent >> cad >> labeled;
         fent >> _nrows >> _ncols;
         if (labeled == "labeled"){
            for (int i=0;i<_nrows;i++){
                fent >> cad;
                _rowLabels.add(Pair(cad,i));
            }
             for (int i=0;i<_ncols;i++){
                fent >> cad;
                _colLabels.add(Pair(cad,i));
            }
        }
        _data = allocate(_nrows,_ncols); 
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" <<endl;
}

Matrix & Matrix::operator*=(double val) {
    for (int i = 0; i < rows(); i++)
        for(int j = 0; j < columns(); j++)
            (*this)(i,j) = (*this)(i,j) * val;
    
    return (*this);
}

Matrix & Matrix::operator+=(double val) {
    for (int i = 0; i < rows(); i++)
        for(int j = 0; j < columns(); j++)
            (*this)(i,j) = (*this)(i,j) + val;
    
    return (*this);
}

Matrix Matrix::operator*(const Matrix & m) const { //multiplcación (*this)*m NO AL REVÉS!!
    
    Matrix product; //constructor sin parámetros pone todo a 0 y nullptr
    double suma_fila;
    
    if(m.rows() == columns()){
        
        product.resize(rows(), m.columns());
        product._colLabels = m._colLabels; //no entiendo muy bien por qué
        
        for(int row = 0; row < rows(); row++){
            for(int col = 0; col < m.columns(); col++){
                suma_fila = 0;
                
                for(int el = 0; el < columns(); el++)
                    suma_fila = suma_fila + at(row,el)*m(el,col);
                
                product(row,col) = suma_fila;
            }
        }
    }
    
    return product;
}

Matrix Matrix::operator+(double val) const {
    Matrix nueva(*this);
    nueva+=val;
    return nueva;
}

Matrix Matrix::operator*(double val) const {
    Matrix nueva(*this);
    nueva*=val;
    return nueva;
}

Matrix operator+(double ival, const Matrix & dch) {   
    return dch.operator +(ival);
}

Matrix operator*(double ival, const Matrix & dch) {   
   return dch.operator *(ival);
}

Matrix & Matrix::normalize(){
    
//    int row = rows();
//    int cols = columns();
//    int suma_fila;
//    
//    for (int i=0; i<row; i++){
//        suma_fila =0;
//        
//        for (int j=0; j<cols; j++)
//            suma_fila += at(i,j);
//        
//        if(suma_fila != 0)
//            for(int k =0; k < cols; k++)
//                _data[i][k] = at(i,k)/suma_fila;
//        else
//            for(int k =0; k <cols; k++)
//                _data[i][k]=1/row;
//    }
//    
//    return (*this);
    for (int i = 0; i < _nrows; i++){
        double result = 0;
        for (int k = 0; k < _ncols; k++)
                result += at(i, k);
        for (int j = 0; j < _ncols; j++){
            if (result != 0)
                at(i, j) /= result;
            else
                at(i, j) = 1.0/_ncols;
        }
    }
    
    return *this;
}