#pragma once
#include <QWidget>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <QString>


class MDRow : QWidget
{
    Q_OBJECT
    public:
        MDRow(QWidget* parent = nullptr); 
        MDRow(QWidget* parent, const std::vector<QWidget>& elements);
        // Move constructor ?
        void addElement(QWidget* element);
        void setMargin(int margin);
        void setSpacing(int margin);
        void clear();
    private:
        void setefRo7ek();
        std::vector<QWidget*> m_elements;
        int m_row_width, m_row_height = 56;
        int m_margin = 32;
        int m_spacing = 16;

        

};



class MDDatatable : QWidget
{
    Q_OBJECT

    public:
        MDDatatable();
        MDDatatable(const MDRow& header, const std::vector<MDRow>& rows);
        void load(const MDRow& header, const std::vector<MDRow>& rows);
        void addRow(MDRow row);
        MDRow getHeader() const;
        std::vector<MDRow> getRows() const;

    private:
        MDRow m_header;
        std::vector<MDRow> m_rows;
};


