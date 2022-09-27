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
        void setAutoResize(bool auto_resize);

        static MDRow* fromStringVector(const std::vector<std::string>& row_data, bool header = false, QWidget* parent = nullptr);
    
    private:
        void setefRo7ek();

        /**
         * @brief Used only by parent datatable to set correct column offsets that matches all rows. this forces testaf. 
         * 
         * @param offsets its size can be bigger than the number of elements. 
         * The last index of this vector is the width of the row. this corresponds to the largest row out of all rows in the parent datatable.
         * @param row_height the height of the row set by parent datatable. used to change the height between header and normal rows
         * 
         */
        void setefRo7ek(const std::vector<int>& offsets, int row_height);
        void showEvent(QShowEvent *event) override;

        std::vector<QWidget*> m_elements;
        /**
         * @brief // this is always 1 element bigger than m_elements. the last offset means where should the next element be put
         * 
         */
        std::vector<int> m_offsets; 
        std::vector<bool> m_truncate_element;
        std::vector<std::string> m_original_text;
        int m_row_width, m_row_height = 52;
        int m_margin = 32;
        int m_spacing = 16;
        bool m_needs_testaf = true;
        bool m_auto_resize = true;
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
        inline std::vector<MDRow*> getRows() const;
        void setAutoResize(bool auto_resize);

        /**
         * @brief resize each column to a custom size. disables auto resize.
         * if a column is bigger than the specified size, it gets truncated.
         * Widgets with text property will have an elipsis at the end.
         * hovering the truncated widget will display the full text.
         * 
         * @param sizes_of_columns an std::vector containing the desired size of each column.
         */
        void resizeColumns(const std::vector<int>& sizes_of_columns);
        void setMaxCharCount(const std::vector<int>& max_chars_of_columns);
        void unlimitCharCount();
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
        bool m_needs_testaf = true;
        bool m_auto_resize = true;
        bool m_chars_limited = false;
        std::vector<int> m_max_chars_of_columns;

        void setefRo7ek();
        void showEvent(QShowEvent *event) override;

        // void hideEvent(QHideEvent *event) override;

};


