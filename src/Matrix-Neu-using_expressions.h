#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <matexpression.h>
#include <vector.h>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };


template <typename T, ORDERING ORD = ORDERING::RowMajor >
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
    
    template <typename TB>
    MatrixView & operator= (const MatExpr<TB> & v2)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = v2((i/v2.get_width()),(i%v2.get_width()) );
      return *this;
    }

    MatrixView & operator= (T scal)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = scal;
      return *this;
    }

    auto View() const { return MatrixView(height_, width_, n_of_elements_, dist_, data_); }
    size_t Get_width() const {return width_;}
    size_t Get_height() const {return height_;}
    size_t Size() const { return n_of_elements_; }

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
                std::cout << RowData[k] << std::endl;
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

        }
    
    
    auto Columns(size_t first, size_t last){
        //selbe probleme wie Rows
        if constexpr(ORD == ORDERING::ColMajor){
            return MatrixView(height_, last-first, data_+(first*height_)*dist_);
        }
    }

  

    auto transpose(){
            if constexpr(ORD == ORDERING::RowMajor){
                return MatrixView<T, ORDERING::ColMajor>(width_,height_,data_);
            }
            else{
                return MatrixView<T, ORDERING::RowMajor>(width_,height_,data_);
            }
        }

    

    /*auto Slice(size_t first, size_t slice) const {
      return MatrixView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
    }*/ //Slice function brauchen wir nicht
      
  };


template <typename T, ORDERING ORD = ORDERING::RowMajor>
    class Matrix : public MatrixView<T,ORD> 
    {
        typedef MatrixView<T,ORD> BASE;
        using BASE::n_of_elements_;
        using BASE::data_;
        
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

        // Konstruktor mit dist?


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

        
        
        //das alles ist schon in MatrixView abgehandelt
        /*size_t get_height() const { return height_;}
        size_t get_width() const { return width_;}
        size_t Size() const { return n_of_elements_; }        
        T & operator()(size_t x, size_t y) { return data_[(x)*width_+y]; }
        const T & operator()(size_t x, size_t y) const { return data_[(x)*width_+y]; }*/


        ~Matrix() {delete [] data_; }


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


        /*Matrix transpose_old(){
    
            T x[n_of_elements_];  //dieses array braucht den allgemeinen typ T, war vorher double
            for(size_t z = 0; z< n_of_elements_;z++){
                x[z] = data_[z];
                
            }
            for(size_t i=0; i<BASE::height_; i++){
                for(size_t j=0; j<BASE::width_; j++){
                    data_[j*BASE::height_+i]=x[i*BASE::width_+j];
                    //should work now -Da
                }
            }


            Matrix<T, ORD> X(BASE::width_, BASE::height_, data_); 
            //height und width sind vertauscht, 3x2.transpose ist 2x3, altes width ist neues height
            return X;
        }*/

        auto transpose(){
            if constexpr(ORD == ORDERING::RowMajor){
                return MatrixView<T, ORDERING::ColMajor>(BASE::width_,BASE::height_,BASE::data_);
            }
            else{
                return MatrixView<T, ORDERING::RowMajor>(BASE::width_,BASE::height_,BASE::data_);
            }
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
   
    //ist schon in ScalMatExpr gelöst worden
    /*template<typename T>
        Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b)
        {
            for(size_t i = 0; i < a.get_height(); i++)
            {
                for(size_t j = 0; j < b.Size(); j+= b.get_width)
                {

                }
            }

        }
*/


}
#endif