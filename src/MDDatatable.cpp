#include "MDDatatable.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>
#include <fmt/format.h>

MDRow::MDRow(QWidget* parent) : QWidget(parent)
{   
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: rgb(255,255,255);");
    m_auto_resize = true;
    m_needs_testaf = true;
}


MDRow::MDRow(const std::vector<QWidget*>& elements, QWidget* parent) : QWidget(parent)
{

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: rgb(255,255,255);");

    for (auto widget : elements)
    {
        widget->setParent(this);
        m_elements.push_back(widget);
    }
    m_auto_resize = true;
    m_needs_testaf = true;

    if (this->isVisible())
    {
        setefRo7ek();
    }


}
void MDRow::addElement(QWidget* element)
{
    element->setParent(this);
    m_elements.push_back(element);
    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }
}

void MDRow::setMargin(int margin)
{
    m_margin = margin;
    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }
}

void MDRow::setSpacing(int spacing)
{
    m_spacing = spacing;
    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }
}


void MDRow::setefRo7ek()
{
    if (this->isVisible())
    {
        if (!m_needs_testaf)
        {
            fmt::print("MDRow msetef already\n");
            return;
        }
            fmt::print("MDRow: setefRo7ek event\n");

        if (m_auto_resize)
        {

            int offset = m_margin; // for the leftmost margin 
            m_offsets.clear();
            m_offsets.push_back(offset);

            for (auto & m_element : m_elements)
            {
                m_element->move(offset, 0);
                offset += m_element->width() + m_spacing;
                m_offsets.push_back(offset);
            }
            // right most margin: m_spacing removed because it was already added in last iteration.
            m_row_width = offset + m_margin - m_spacing;
            this->setFixedSize(m_row_width, m_row_height);

        }
        else // m_offsets is set inside of MDRow::resizeColumns().
        {
            if (m_offsets.size() < m_elements.size())
            {
                fmt::print("invalid m_offsets. its size: {} less than m_elements's size:{}", m_offsets.size(), m_elements.size());
                return;
            }
            for (int i = 0; i < m_elements.size(); i++)
            {
                m_elements[i]->move(m_offsets[i], 0);
            }
            if (m_offsets.size() > 0)
            {
                m_row_width = m_offsets[m_offsets.size() - 1] + m_margin - m_spacing;
            }
            this->setFixedSize(m_row_width, m_row_height);
        }
            
        m_needs_testaf = false;

    }
    else
    {
        fmt::print("Warning MDRow: Make sure MDRow is visible for proper rendering\n");
    }
   
}



void MDRow::setefRo7ek(const std::vector<int>& offsets, int row_height)
{
    if (this->isVisible())
    {
        fmt::print("MDRow: setefRo7ek event forced by datatable\n");

        m_offsets.clear();
        if (offsets.size() < m_elements.size() + 1)
        {
            fmt::print("Warning MDRow setefRo7ek: size of argument offsets = {} is less to internal size of m_offsets {}\n", offsets.size(), m_elements.size());
            return;
        }
        
        for (int i = 0; i < m_elements.size(); i++) 
        {
            m_offsets.push_back(offsets[i]);
            m_elements[i]->setFixedHeight(row_height);
            m_elements[i]->move(m_offsets[i], 0);
        }

        m_row_height = row_height;
        // last index of argument offsets means the width of the entire datatable
        m_row_width = offsets[offsets.size() - 1];  
        // however for the internal m_offsets of any individual row, the last index means where should the next element be put
        if (m_offsets.size() > 0 && m_elements.size() > 0)
            m_offsets.push_back(m_offsets[m_offsets.size() - 1] + m_elements[m_elements.size() - 1]->width() +  m_spacing);
        
        this->setFixedSize(m_row_width, m_row_height);
    }
    else
    {
        fmt::print("Warning MDRow: Make sure MDRow is visible for proper rendering (forced)\n");
    }

}

void MDRow::clear()
{
    for (auto element : m_elements)
    {
        delete element;
    }
    m_elements.clear();
}



MDRow* MDRow::fromStringVector(const std::vector<std::string>& row_data, bool header, QWidget* parent)
{
    
    std::vector<QWidget*> elements;
    for (const auto& str: row_data)
    {
        auto lbl = new QLabel(QString::fromStdString(str));
        if (header)
        {
            lbl->setStyleSheet("font-family: \"Arial\"; font-size: 14px; font-weight : 700;");
        }
        else
        {
            lbl->setStyleSheet("font-family: \"Arial\"; font-size: 14px; font-weight : 400;");
        }
        elements.push_back(lbl);
    }
    
    return new MDRow(elements, parent);
}



void MDRow::showEvent(QShowEvent *event)
{

    if (this->isVisible() && m_needs_testaf)
    {
        setefRo7ek();
    }
    
}

void MDRow::resizeColumns(const std::vector<int>& sizes_of_columns)
{
    m_auto_resize = false;
    m_needs_testaf = true;

    m_offsets.clear();
    m_offsets.push_back(m_margin);
    for (int i = 0; i < sizes_of_columns.size(); i++)
    {
        m_offsets.push_back(sizes_of_columns[i] + m_offsets[i] + m_spacing); 
    }

    if (this->isVisible())
    {
        setefRo7ek();
    }
}




void MDRow::setAutoResize(bool auto_resize)
{
    m_auto_resize = auto_resize;
}






MDDatatable::MDDatatable(QWidget* parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: rgb(200,200,200);");
}


MDDatatable::MDDatatable(const std::vector<MDRow*>& rows, QWidget* parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: rgb(200,200,200);");
    for(int i = 0; i < rows.size(); i++)
    {
        m_rows.push_back(rows[i]);
        m_rows[i]->setParent(this);
    }
    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }
} 


void MDDatatable::addRow(MDRow* row)
{

    row->setParent(this);
    row->show();
    m_rows.push_back(row);

    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }

}


void MDDatatable::setefRo7ek()
{

    if (!m_needs_testaf)
    {
        fmt::print("MDRow msetef already\n");
        return;
    }
    fmt::print("MDDatatable: setefRo7ek event\n");
    if (this->isVisible())
    {
        m_cols_offsets.clear();
        m_rows_offsets.clear();

        if (m_auto_resize)
        {


            // represents max length (ie where to put the next element)
            std::vector<int> biggest_columns_sizes;
            for (auto& m_row : m_rows)
            {

                for (int j = 0; j < m_row->m_elements.size(); j++)
                {
                    if (j >= biggest_columns_sizes.size())
                    {
                        biggest_columns_sizes.push_back(0);
                    }
                    
                    if (m_row->m_elements[j]->width() > biggest_columns_sizes[j])
                    {
                        biggest_columns_sizes[j] = m_row->m_elements[j]->width();
                    }
                } 
            }



            // TODO: You can prolly think harder on this and try to put inside the previous loops where biggest_column_sizes is getting updated.
            // for now im leaving it like this
            
            m_cols_offsets.push_back(m_column_margin);
            for (int i = 0; i < biggest_columns_sizes.size(); i++)
            {
                m_cols_offsets.push_back(m_cols_offsets[i] +  biggest_columns_sizes[i] + m_column_spacing);
            }
            m_cols_offsets[m_cols_offsets.size() - 1] += m_column_margin - m_column_spacing;


            for (int i = 0; i < m_rows.size(); i++)
            {
                
                if (i == 0)
                {
                    m_rows[0]->setefRo7ek(m_cols_offsets, m_header_height);
                    m_rows[0]->move(0, 0);
                    m_rows_offsets.push_back(0);
                    m_rows_offsets.push_back(m_header_height + m_row_spacing);
                }
                else
                {
                    m_rows[i]->setefRo7ek(m_cols_offsets, m_normal_rows_height);
                    m_rows[i]->move(0, m_rows_offsets[i]);
                    m_rows_offsets.push_back(m_rows_offsets[i] + m_normal_rows_height + m_row_spacing);
                }

            }
            m_table_height = m_rows_offsets[m_rows_offsets.size() - 1] - m_row_spacing;
            m_table_width = m_cols_offsets[m_cols_offsets.size() - 1];
            this->setFixedSize(m_table_width, m_table_height);
        }
        else
        {
            for (int i = 0; i < m_rows.size(); i++)
            {
                
                if (i == 0)
                {
                    m_rows[0]->move(0, 0);
                    m_rows_offsets.push_back(0);
                    m_rows_offsets.push_back(m_header_height + m_row_spacing);
                    for (const auto& offset: m_rows[0]->m_offsets)
                    {
                        m_cols_offsets.push_back(offset);
                    }
                    m_table_width = m_rows[0]->width();
                }
                else
                {

                    m_rows[i]->move(0, m_rows_offsets[i]);
                    m_rows_offsets.push_back(m_rows_offsets[i] + m_normal_rows_height + m_row_spacing);
                }

            }
            m_table_height = m_rows_offsets[m_rows_offsets.size() - 1] - m_row_spacing;
            this->setFixedSize(m_table_width, m_table_height);
        }
        // assumes that there is already offsets in the MDRow (i.e. setefRo7ek() was called once in the MDRow)
       
        

        m_needs_testaf = false;
    }
    else
    {
        fmt::print("Warning MDDatatable: Make sure MDDatatable is visible for proper rendering\n");
    }
    
}

void MDDatatable::load(const std::vector<MDRow*>& rows)
{
    m_rows.clear();
    for(int i = 0; i < rows.size(); i++)
    {
        m_rows.push_back(rows[i]);
        m_rows[i]->setParent(this);
        m_rows[i]->show();
        
    }
    m_needs_testaf = true;
    if (this->isVisible())
    {
        setefRo7ek();
    }
} 

void MDDatatable::showEvent(QShowEvent *event)
{

    if (this->isVisible())
    {
        if (m_needs_testaf)
        {
            setefRo7ek();
        }
    }
}
inline std::vector<MDRow*> MDDatatable::getRows() const
{
    return m_rows;
}



void MDDatatable::resizeColumns(const std::vector<int>& sizes_of_columns)
{
    m_auto_resize = false;
    m_needs_testaf = true;

    int max_width = 0;
    for (auto row: m_rows)
    {
        row->resizeColumns(sizes_of_columns);

    }   
    if (this->isVisible())
    {
        setefRo7ek();
    }
}



void MDDatatable::setAutoResize(bool auto_resize)
{
    m_auto_resize = auto_resize;
}
