#pragma once
#include <QWidget>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <QString>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>

class MDRow : public QWidget
{
    Q_OBJECT
    public:
        MDRow(QWidget* parent = nullptr); 
        MDRow(const std::vector<QWidget*>& elements, QWidget* parent = nullptr);
        // Move constructor ?
        void addElement(QWidget* element);
        void setMargin(int margin);
        void setSpacing(int margin);
        void clear();

        static MDRow* fromStringVector(const std::vector<std::string>& row_data, bool header = false, QWidget* parent = nullptr);
    private:
        void setefRo7ek();

        /**
         * @brief Used only by parent datatable to set correct column offsets that matches all rows. 
         * 
         * @param offsets its size can be bigger than the number of elements. 
         * The last index of this vector is the width of the row. this corresponds to the largest row out of all rows in the parent datatable.
         * @param row_height the height of the row set by parent datatable. used to change the height between header and normal rows
         * 
         */
        void setefRo7ek(const std::vector<int>& offsets, int row_height);

        std::vector<QWidget*> m_elements;
        std::vector<int> m_offsets; // this is always 1 element bigger than m_elements. the last offset means where should the next element be put
        int m_row_width, m_row_height = 56;
        int m_margin = 32;
        int m_spacing = 16;



    friend class MDDatatable;
        

};



class MDDatatable : public QWidget
{
    Q_OBJECT

    public:
        MDDatatable(QWidget* parent = nullptr);
        MDDatatable(const std::vector<MDRow*>& rows, QWidget* parent = nullptr);
        void load(const std::vector<MDRow*>& rows);
        
        void addRow(MDRow* row);
        std::vector<MDRow*> getRows() const;

    private:
        std::vector<MDRow*> m_rows;
        int m_table_width, m_table_height;
        std::vector<int> m_rows_offsets;
        std::vector<int> m_cols_offsets;
        int m_header_height = 56;  
        int m_normal_rows_height = 52;
        int m_row_spacing = 1;  // spacing between each row
        int m_column_spacing = 16;
        int m_column_margin = 32;
        void setefRo7ek();
};


