#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include "mat_vec_decl.h"
#include "matexpression.h"
//#include "vector.h"

namespace ASC_bla
{
//enum ORDERING { ColMajor, RowMajor };


template <typename T, ORDERING ORD> 
  class MatrixView : public MatExpr<MatrixView<T,ORD>>
  {
  protected:
    T * data_;
    size_t height_;
    size_t width_;
    size_t n_of_elements_;
    size_t dist_ = 1;
  public:
    MatrixView (size_t height, size_t width, T * data)
      : height_(height), width_(width), data_(data), n_of_elements_(height*width) { }
    
    /*den constructor kann man=Felix nicht aufrufen weil der TDIST type probleme macht
    wenn ich MatrixView(1,1, new T[1], 1) mache erkennt er das TDIST argument als int und sagt er hat keine
    "matching function", wenn ich den letzen einser als: std::integral_constant<size_t,1> übergebe erwartet er
    eine "primary expression", soll heissen std::integral... ist zu komplex als funktionsargument*/
    MatrixView (size_t height, size_t width, T * data, size_t dist)
      :  height_(height), width_(width), data_(data), n_of_elements_(height*width), dist_(dist) { }
    
    MatrixView (size_t height, size_t width)
      :  height_(height), width_(width), n_of_elements_(height*width), data_(new T[height*width]) { }

    template <typename TB>
    MatrixView & operator= (const MatExpr<TB> & v2)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = v2((i/v2.Get_width()),(i%v2.Get_width()) );
      return *this;
    }

    MatrixView & operator= (T scal)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = scal;
      return *this;
    }


    template <typename TB>
    MatrixView & operator+= (const MatExpr<TB> & v2)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] += v2((i/v2.Get_width()),(i%v2.Get_width()) );
      return *this;
    }

    MatrixView & operator*= (T scal)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] *= scal;
      return *this;
    }


    

    auto View() const { return MatrixView(height_, width_, n_of_elements_, dist_, data_); }
    size_t Get_width() const {return width_;}
    size_t Get_height() const {return height_;}
    size_t Size() const { return n_of_elements_; }
    size_t Dist() const {
        if constexpr (ORD == RowMajor){
            return width_; 
            }
        else { //heist ORD == ColMajor
            return height_;
            }
    }
    auto Data() const {return data_;}

    T & operator()(size_t x, size_t y) {
        if constexpr (ORD == RowMajor){
            return data_[dist_*(x*width_+y)]; 
            }
        else { //heist ORD == ColMajor
            return data_[dist_*(x+y*height_)];
            }
        }

    const T & operator()(size_t x, size_t y) const {
        if constexpr (ORD == RowMajor){
            return data_[dist_*(x*width_+y)]; 
            }
        else { //heist ORD == ColMajor
            return data_[dist_*(x+y*height_)];
            }
        }
    
    auto Range(size_t first_x, size_t first_y, size_t next_x, size_t next_y) const {
      return MatrixView((next_x-first_x),(next_y-first_y), data_+(first_x)*width_+first_y*dist_, dist_);
    } 
    //Range funktioniert für (0,0,1,2) --> gibt nur erste Zeile aus
    //Range funktioniert nur so halb für (0,0,2,1) --> gibt nur eine Spalte aus 
    //(aber immer noch nur die ersten 2 Einträge <--falsch)



    // Row/Col mit VectorView - OHNE DIST BERUECKSICHTUNG :(
    auto Row(size_t i) const {
        if constexpr (ORD == RowMajor) {
            return VectorView(width_, data_+(i*width_));
        }
        else { //heisst ORD == ColMajor
            T* RowData = new T[width_];
            for (int k = 0; k < width_; k++) {
                RowData[k] = data_[i + k*height_];
            }
            return VectorView(width_, RowData);
        }
    }

    auto Column(size_t i) const {
        if constexpr (ORD == RowMajor) {
            T* ColData = new T[height_];
            for (int k = 0; k < height_; k++) {
                ColData[k] = data_[i*dist_ + k*width_]; // dist?
            }
            return VectorView(height_, ColData);
        }
        else { //heisst ORD == ColMajor
            return VectorView(height_, data_+i*(height_));
        }
    }
    
    auto Rows(size_t first, size_t last){
        //error handling: first > last
        //sonderfall Rows wird zu Row eventuell
        if constexpr(ORD == ORDERING::RowMajor){
            return MatrixView(last-first, width_, data_+(first*width_)*dist_);
        }
        if constexpr(ORD == ORDERING::ColMajor){
            T* RowData = new T[(last-first)*height_];
            data_ += first;
            for(int i = 0; i < width_;i++){
                for(int j = 0; j < (last-first);j++){
                    RowData[j+i*(last-first)] = data_[j+i*(height_)];
                }
            }
            data_ -= first;
            return MatrixView((last-first),width_,RowData);
        }
    }
    
    
    auto Columns(size_t first, size_t last){
        //selbe probleme wie Rows
        if constexpr(ORD == ORDERING::ColMajor){
            return MatrixView(height_, last-first, data_+(first*height_)*dist_);
        }
        if constexpr(ORD == ORDERING::RowMajor){
            T* ColumnData = new T[(last-first)*height_];
            data_ += first;
            for (int k = 0; k < height_; k++){
                for (int j = 0; j < (last-first); j++){
                    ColumnData[k*(last-first)+j] = data_[j+k*width_];
                }
            }
            data_ -= first; //got a weird assertion in Visual Studio Code, this might fix it
            return MatrixView(height_,(last-first),ColumnData);
        }
    }
  
    auto Diag(){
        return VectorView(height_, (dist_+width_), data_); // nur für width
    }

    auto transpose(){
            if constexpr(ORD == ORDERING::RowMajor){
                return MatrixView<T, ORDERING::ColMajor>(width_,height_,data_);
            }
            else{
                return MatrixView<T, ORDERING::RowMajor>(width_,height_,data_);
            }
    }

    void swapRows(size_t row1, size_t row2) {
        for (size_t col = 0; col < width_; ++col) {
            std::swap(data_[row1 * width_ + col], data_[row2 * width_ + col]);
        }
    }

    // Inverse mit Gauss-Elimination
    //has been simplified using new features Row (i)
    //still no option to inverse ColMajors
    auto inverse() { 
        if (width_ != height_) {
            throw std::invalid_argument("Non-square matrix, inverse does not exist!"); // TODO: zu error machen
        }

        // Identity matrix
        T* id_data = new T[n_of_elements_]{0};
        MatrixView<T> id_mat(height_, width_, id_data); // TODO: dist?
        for (int i=0; i < height_; i++) {
            id_mat(i,i) = 1;
        }

        // ursprüngliche Matrix kopieren, sodass diese nicht verändert wird
        MatrixView<T> copy_mat(height_, width_, data_);
        //if(ORD == ORDERING::ColMajor){copy_mat = this->transpose;}

        // Inverse berechnen
        for (size_t i=0; i < height_; i++) { 
            
            // Zeilenvertauschung falls notwendig
            size_t maxRow = i;
            for (size_t k = i + 1; k < height_; k++) {
                if (std::abs(copy_mat(k, i)) > std::abs(copy_mat(maxRow, i))) {
                    maxRow = k;
                }
            }
            if (maxRow != i) {
                // Zeilen vertauschen
                copy_mat.swapRows(i, maxRow);
                id_mat.swapRows(i, maxRow);
            }

            // i-te Zeile durch (i,i)-ten Eintrag dividieren:
            T diag_element = copy_mat(i, i);
            if (diag_element == 0) { std::cout << "Matrix ist singulaer" << std::endl;} // TODO: zu error machen
            //copy_mat.Row(i) = (1/diag_element) * copy_mat.Row(i);
            //id_mat.Row(i) = (1/diag_element) * id_mat.Row(i);
            copy_mat.Row(i) /= diag_element;
            id_mat.Row(i) /= diag_element;
            
            // andere Zeilen eliminieren:
            for (int k=0; k < height_; k++) { 
                if (k != i) {
                    T factor = copy_mat(k, i);
                    copy_mat.Row(k) = copy_mat.Row(k) - (factor * copy_mat.Row(i));
                    id_mat.Row(k) = id_mat.Row(k) - (factor * id_mat.Row(i));

                }
            }
        }
        if (ORD == ORDERING::ColMajor) { id_mat = id_mat.transpose(); }
            // -> Inverse der transp. Matrix == Transponierte der inv. Matrix (fkt. aber nicht)
            // falls das so nix wird beim Initialisieren von id_mat Fallunterscheidung für ColMajor machen
        return id_mat;
    }
    
    // Inverse mit Gauss-Elimination
    //has been simplified using new features Row (i)
    //still no option to inverse ColMajors
    /*auto inverse() { 
        if (width_ != height_) {
            std::cout << "Nicht quadratische Matrix!" << std::endl; // TODO: zu error machen
        }

        // Identity matrix
        T* id_data = new T[n_of_elements_]{0};
        MatrixView<T> id_mat(height_, width_, id_data); // TODO: dist?
        for (int i=0; i < height_; i++) {
            id_mat(i,i) = 1;
        }

        // ursprüngliche Matrix kopieren, sodass diese nicht verändert wird
        MatrixView<T> copy_mat(height_, width_, data_);
        //if(ORD == ORDERING::ColMajor){copy_mat = this->transpose;}

        // Inverse berechnen
        for (int i=0; i < height_; i++) { 

            // i-te Zeile durch (i,i)-ten Eintrag dividieren:
            T diag_element = copy_mat(i, i);
            if (diag_element == 0) { std::cout << "Matrix ist singulaer" << std::endl;} // TODO: zu error machen
            copy_mat.Row(i) = (1/diag_element) * copy_mat.Row(i);
            id_mat.Row(i) = (1/diag_element) * id_mat.Row(i);
            
            // andere Zeilen eliminieren:
            for (int k=0; k < height_; k++) { 
                if (k != i) {
                    T factor = copy_mat(k, i);
                    copy_mat.Row(k) = copy_mat.Row(k) - (factor * copy_mat.Row(i));
                    id_mat.Row(k) = id_mat.Row(k) - (factor * id_mat.Row(i));

                }
            }
        }
        if (ORD == ORDERING::ColMajor) { id_mat = id_mat.transpose(); }
            // -> Inverse der transp. Matrix == Transponierte der inv. Matrix (fkt. aber nicht)
            // falls das so nix wird beim Initialisieren von id_mat Fallunterscheidung für ColMajor machen
        return id_mat;
    }*/

    

    /*auto Slice(size_t first, size_t slice) const {
      return MatrixView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
    }*/ //Slice function brauchen wir nicht
      
  };



template <typename T = double, ORDERING ORD = ORDERING::RowMajor>
    class Matrix : public MatrixView<T,ORD> 
    {
        typedef MatrixView<T,ORD> BASE;
        using BASE::n_of_elements_;
        using BASE::data_;
        using BASE::dist_;
        
        public:
        //alle Matrix() kontruktor sind nur pseudo-konstruktor da wir einfach den dazugehörigen MatrixView konstruktor
        //aufrufen und passend befüllen

        Matrix()    //Standard-Konstruktor --1x1 Matrix mit Nullelement
            : MatrixView<T, ORD> (1, 1, new T[1]){data_[0]= 0.0; }
            /*Matrix() erstellt ein MatrixView object, constructor von oben, mit height1, width1, n_elements1 und einem
            1x1 array wo 0 drinnen ist*/

        Matrix (size_t height, size_t width)
            : MatrixView<T, ORD> (height, width, new T[height*width])
        { for (size_t i = 0; i < n_of_elements_; i++)    //füllt Matrix Element für Element mit 0
            data_[i] = 0.0;
        }

        Matrix (size_t height, size_t width, const T* inputdata)
            : MatrixView<T,ORD> (height, width, new T[height*width]) 
        { for (size_t i = 0; i < n_of_elements_; i++)
            data_[i] = inputdata[i];
        }

        Matrix (size_t height, size_t width, const T* inputdata, size_t dist)
            : MatrixView<T,ORD> (height, width, new T[height*width], dist) 
        { for (size_t i = 0; i < n_of_elements_; i++)
            data_[i] = inputdata[i];
        }


        Matrix (const Matrix & m)       //wenn Matrix übergeben, muss nix verändert werden?
            : Matrix(m.Get_height(),m.Get_width())
        {
            *this = m;
        }

        Matrix (Matrix && m)
            : MatrixView<T,ORD> (0, 0, nullptr)
        {
            std::swap(BASE::height_, m.height_);
            std::swap(BASE::width_, m.width_);
            std::swap(n_of_elements_, m.n_of_elements_);
            std::swap(data_, m.data_);
        }

        /*Matrix (initializer_list<initializer_list<T>> llist) : FlatMatrix<T,ORD> (0,0,nullptr)
        {
            int h = llist.size();
            int w = 0;
            for (auto row : llist)
            w = std::max(w, int(row.size()));

            SetSize (h, w);
            (*this) = T(0.0);

            int r = 0;
            for (auto row : llist)
            {
                int c = 0;
                for (auto col : row)
                (*this)(r,c++) = col;
                r++;
            }
        }*/

        
        
        //das alles ist schon in MatrixView abgehandelt
        /*size_t get_height() const { return height_;}
        size_t get_width() const { return width_;}
        size_t Size() const { return n_of_elements_; }        
        T & operator()(size_t x, size_t y) { return data_[(x)*width_+y]; }
        const T & operator()(size_t x, size_t y) const { return data_[(x)*width_+y]; }*/


        ~Matrix() {delete [] data_; }


        using BASE::operator=; // enables Matrix = MatrixView, e.g. A = B.transpose(), C=A*B, etc..

        Matrix & operator=(const Matrix & v2)
        {

            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.Get_width()) ,(i%v2.Get_width()) );     
            return *this;
        }

        Matrix & operator=(Matrix && v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.Get_width())  ,(i%v2.Get_width()));     
            return *this;
        }


        
    };
    
    template <typename ...Args>
    std::ostream & operator<< (std::ostream & ost, const MatrixView<Args...> & v)
    {
        for (size_t i = 0; i < v.Get_height(); i++){
            for (size_t j = 0; j < v.Get_width(); j++){
                if(j==0){
                    ost << v(i,j);
                }
                if(j>0){
                    ost << ", " << v(i,j);
                }
            }
            ost << std::endl; 
            
            //if(i%(v.get_width-1)==0){
                //ost << std::endl;
            //}
        }
        return ost;
    }

}
#endif