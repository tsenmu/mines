#include "minesfailuredialog.h"
#include "ui_minesfailuredialog.h"
#include <QTime>

MinesFailureDialog::MinesFailureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MinesFailureDialog)
{
    ui->setupUi(this);
    quotes << "\"I have not failed. I've just found 10,000 ways that won't work.\" -- Thomas A. Edison"
           << "\"Success is not final, failure is not fatal: it is the courage to continue that counts.\" -- Winston Churchill"
           << "\"There is only one thing that makes a dream impossible to achieve: the fear of failure.\" -- Paulo Coelho, The Alchemist"
           << "\"Pain is temporary. Quitting lasts forever.\" -- Lance Armstrong, Every Second Counts "
           << "\"Failure is the condiment that gives success its flavor.\" -- Truman Capote"
           << "\"To err is human, to forgive, divine.\" -- Alexander Pope, An Essay on Criticism "
           << "\"Success is stumbling from failure to failure with no loss of enthusiasm.\" -- Winston Churchill"
           << "\"Have no fear of perfection - you'll never reach it\" -- Salvador Dalí"
           << "\"Don't spend time beating on a wall, hoping to transform it into a door.\" -- Coco Chanel"
           << "\"My fault, my failure, is not in the passions I have, but in my lack of control of them.\" -- Jack Kerouac"
           << "\"Life is full of screwups. You're supposed to fail sometimes. It's a required part of the human existance.\" -- Sarah Dessen, Along for the Ride"
           << "\"I didn't fail the test, I just found 100 ways to do it wrong.\" -- Benjamin Franklin"
           << "\"Just because you fail once doesn't mean you're gonna fail at everything.\" -- Marilyn Monroe"
           << "\"It is hard to fail, but it is worse never to have tried to succeed.\" -- Theodore Roosevelt"
           << "\"I make mistakes like the next man. In fact, being--forgive me--rather cleverer than most men, my mistakes tend to be correspondingly huger.\" -- J.K. Rowling, Harry Potter and the Half-Blood Prince";
    qsrand(QTime::currentTime().msec());
    ui->label_quote->setText(quotes[qrand() % quotes.length()]);
}

MinesFailureDialog::~MinesFailureDialog()
{
    delete ui;
}

void MinesFailureDialog::on_pushButton_replay_clicked()
{
    this->accept();
}

void MinesFailureDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}
