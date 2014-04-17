#include "dialognewwebio.h"
#include "ui_DialogNewWebIO.h"
#include "formrules.h"

DialogNewWebIO::DialogNewWebIO(Room *r, int item, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DialogNewWebIO), io(NULL), room(r), item(item)
{
        ui->setupUi(this);

        //hide error labels by default.
        ui->label_error_empty->hide();
        ui->label_error_path_empty->hide();
        ui->label_error_url_empty->hide();

        // Set default combo type value
        switch (item)
        {
        case ITEM_TEMP:
                ui->io_type->setCurrentIndex(0);
                break;
        case ITEM_ANALOG:
                ui->io_type->setCurrentIndex(1);
                break;
        case ITEM_STRING:
                if (type.find("Input") != string::npos)
                        ui->io_type->setCurrentIndex(2);
                else
                        ui->io_type->setCurrentIndex(3);
                break;
        default:
                break;
        }
}

DialogNewWebIO::~DialogNewWebIO()
{
        delete ui;
}

void DialogNewWebIO::changeEvent(QEvent *e)
{
        QDialog::changeEvent(e);
        switch (e->type())
        {
           case QEvent::LanguageChange:
                ui->retranslateUi(this);
                break;
           default:
                break;
        }
}

void DialogNewWebIO::on_buttonBox_accepted()
{
        if (ui->edit_name->text().isEmpty())
        {
                ui->label_error_empty->show();
                return;
        }
        else if (ui->label_error_path_empty->text().isEmpty())
        {
                ui->label_error_path_empty->show();
                return;
        }
        else if (ui->label_error_url_empty->text().isEmpty())
        {
                ui->label_error_url_empty->show();
                return;
        }

        Params p;
        p.Add("name", ui->edit_name->text().toUtf8().constData());
        switch (ui->io_type->currentIndex())
        {
        case 1:
                type = "WebInputTemp";
                break;
        case 2:
                type = "WebInputAnalog";
                break;
        case 3:
                type = "WebInputString";
                break;
        case 4:
                type = "WebOutputString";
                break;
        default:
                break;
        }
        p.Add("type", type);
        p.Add("url", to_string(ui->edit_url->text().toUtf8().constData()));
        p.Add("path", to_string(ui->edit_path->text().toUtf8().constData()));
        p.Add("file_type", to_string(ui->data_type->currentText().toLower().toUtf8().constData()));

        io = ListeRoom::Instance().createInput(p, room);
        accept();
}