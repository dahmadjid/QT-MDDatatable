#include "MDDatatable.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>
MDRow::MDRow(QWidget* parent) : QWidget(parent)
{   

    bool k = true;
    this->setFixedSize(500,100);

    for (int i = 0; i < 5; i++)
    {
        std::string text = "hello";
        text += (char)(i + '0');
        QLabel* lbl = new QLabel();
        lbl->setText(QString::fromStdString(text));
        this->addElement(lbl);
        // if (k)
        // {
        //     lbl->setText("azeazeazeazeazeazezaeazeazeaz");
        //     std::cout << lbl->width() <<  std::endl;
        //     QTimer::singleShot(1000, this, [=]{
        //         std::cout << lbl->width() <<  std::endl;
        //     }); 
        //     lbl->setMaximumWidth(60);
        //     k = false;
        // }
            //      QTimer::singleShot(1000, this, [=]{
            //     std::cout << lbl->width() <<  std::endl;
            // }); 
        

    }
    QTimer::singleShot(1000, this, [=]{setefRo7ek();}); 

}


MDRow::MDRow(QWidget* parent, const std::vector<QWidget>& elements) : QWidget(parent)
{

}

void MDRow::setefRo7ek()
{
    if (this->isVisible())
    {
        
        int offset = 32; // for the leftmost margin 
        for (int i = 0; i < m_elements.size(); i++)
        {
            m_elements[i]->move(offset, 0);
            offset += m_elements[i]->width() + 16; // for margin between each
        }
        offset += 16; // right most margin: 16 was already added in last iteration so adding another will make it 32 like the left most margin
        this->setFixedSize(offset, m_row_height);
        m_row_width = offset;
    }
    else
    {
        std::cout << "Warning MDRow: Make sure MDDatatable is visible for proper rendering" << std::endl;
    }
   
}

void MDRow::addElement(QWidget* element)
{
    element->setParent(this);
    m_elements.push_back(element);
    setefRo7ek();
}

void MDRow::clear()
{
    m_elements.clear();
}


void MDRow::setMargin(int margin)
{
    m_margin = margin;
    setefRo7ek();
}

void MDRow::setSpacing(int spacing)
{
    m_spacing = spacing;
    setefRo7ek();
}

MDDatatable::MDDatatable()
{

} 

void MDDatatable::load(const MDRow& header, const std::vector<MDRow>& rows)
{

} 
