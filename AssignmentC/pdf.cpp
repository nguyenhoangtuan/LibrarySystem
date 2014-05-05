#include <QTextDocument>
#include <QPrinter>
#include <QApplication>
#include "datamodel.h"
#include "pdf.h"
#include <QString>

void PDF::pdf_file()
{

  QString a = "<p><b><center>Collection List</b></center></p>";
  vector<Collection> items = DataModel::getCollectionList();
  for(int i = 0; i < items.size(); i++) {
    a +="<p>" + QString::number(((Collection)items[i]).getId()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getCategory()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getDataType()) + "</p>";
    a +="<p>" + QString::number(((Collection)items[i]).getDuration()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getPublisher()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getTitle()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getType()) + "</p>";
    a +="<p>" + QString::fromStdString(((Collection)items[i]).getVersion()) + "</p>";
    a +="<p>" + QString::number(((Collection)items[i]).getYearRecored()) + "</p>";
    a +="<p>==============================</p>";
  }

    a +="<p><center><b>Items Borrowed List</b><center></p>";
  vector<Item> itemv = DataModel::getItemList();
  for(int i = 0; i < itemv.size(); i++) {
     a +="<p>" + QString::number(((Item)itemv[i]).getId()) + "</p>";
     a +="<p>" + QString::number(((Item)itemv[i]).getBarcode()) + "</p>";
     a +="<p>" + QString::fromStdString(((Item)itemv[i]).getBorrowStatus()) + "</p>";
     a +="<p>" + QString::number(((Item)itemv[i]).getBorrTime()) + "</p>";
     a +="<p>" + QString::fromStdString(((Item)itemv[i]).getDateBorr()) + "</p>";
     a +="<p>" + QString::number(((Item)itemv[i]).getDayBorr()) + "</p>";
     a +="<p>" + QString::number(((Item)itemv[i]).getIdenCode()) + "</p>";
     a +="<p>-------------------------------------------</p>";
  }

  a +="<p><center><b>Borrowers List</b><center></p>";
    vector<Borrower> brr = DataModel::getBorrList();
    for(int i = 0; i < brr.size(); i++) {
        a +="<p>" + QString::number(((Borrower)brr[i]).getId()) + "</p>";
        a +="<p>" + QString::fromStdString(((Borrower)brr[i]).getName()) + "</p>";
        a +="<p>" + QString::fromStdString(((Borrower)brr[i]).getType()) + "</p>";
        a +="<p>" + QString::fromStdString(((Borrower)brr[i]).getDepartment()) + "</p>";
        a +="<p>" + QString::number(((Borrower)brr[i]).getItemBorr()) + "</p>";
        a +="<p>" + QString::number(((Borrower)brr[i]).getItemLate()) + "</p>";
        a +="<p>" + QString::fromStdString(((Borrower)brr[i]).getItemString()) + "</p>";
        a +="<p>" + QString::fromStdString(((Borrower)brr[i]).getMobileNumber()) + "</p>";
        a +="<p>++++++++++++++++++++++++++++++++++++++</p>";
  }

  QTextDocument doc;
  doc.setHtml(a);

   QPrinter printer;
   printer.setOutputFileName("Assingment_2_s3408665.pdf");
   printer.setOutputFormat(QPrinter::PdfFormat);
   doc.print(&printer);
   printer.newPage();
   QMessageBox msgBox;
   msgBox.setText("Creating PDF file Successfully!!");
   msgBox.exec();

}

