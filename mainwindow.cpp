// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollArea>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTabWidget *tabs = new QTabWidget(this);
    QWidget *paperLikeTab = new QWidget();
    QWidget *modernTab = new QWidget();
    tabs->addTab(paperLikeTab, "Интерфейс №1");
    tabs->addTab(modernTab, "Интерфейс №2");
    setCentralWidget(tabs);

    // ВЕРСИЯ 1
    QVBoxLayout *layout1 = new QVBoxLayout(paperLikeTab);

    QLabel *topLabel = new QLabel("Унифицированная форма № ОП-19\nУтверждена постановлением Госкомстата России от 25.12.98 № 132");
    topLabel->setAlignment(Qt::AlignCenter);
    layout1->addWidget(topLabel);

    QGroupBox *requisitesBox = new QGroupBox("Основные реквизиты");
    QFormLayout *requisitesLayout = new QFormLayout(requisitesBox);
    requisitesLayout->addRow("Код формы по ОКУД:", new QLabel("0330519"));
    requisitesLayout->addRow("по ОКПО:", new QLineEdit());
    requisitesLayout->addRow("Организация:", new QLineEdit());
    requisitesLayout->addRow("Структурное подразделение:", new QLineEdit());
    requisitesLayout->addRow("Вид деятельности по ОКДП:", new QLineEdit());
    layout1->addWidget(requisitesBox);

    QLabel *title = new QLabel("ЖУРНАЛ УЧЕТА СТОЛОВОЙ ПОСУДЫ И ПРИБОРОВ, ВЫДАВАЕМЫХ ПОД ОТЧЕТ РАБОТНИКАМ ОРГАНИЗАЦИИ");
    title->setAlignment(Qt::AlignCenter);
    layout1->addWidget(title);

    // Строка с периодом
    QHBoxLayout *periodLayout = new QHBoxLayout();
    periodLayout->addStretch();
    periodLayout->addWidget(new QLabel("за период с"));
    QLineEdit *periodFrom = new QLineEdit();
    periodFrom->setFixedWidth(100);
    periodLayout->addWidget(periodFrom);
    periodLayout->addWidget(new QLabel("по"));
    QLineEdit *periodTo = new QLineEdit();
    periodTo->setFixedWidth(100);
    periodLayout->addWidget(periodTo);
    periodLayout->addWidget(new QLabel("года"));
    periodLayout->addStretch();
    layout1->addLayout(periodLayout);

    layout1->addSpacing(15);

    // Блок: Лицо, ответственное за ведение журнала
    QVBoxLayout *journalResponsibleBlock = new QVBoxLayout();

    // Первая строка
    QHBoxLayout *responsibleLine1 = new QHBoxLayout();
    responsibleLine1->addWidget(new QLabel("Лицо, ответственное за ведение журнала"));

    QLineEdit *journalPosition = new QLineEdit();
    journalPosition->setPlaceholderText("должность");
    journalPosition->setFixedWidth(150);
    responsibleLine1->addSpacing(10);
    responsibleLine1->addWidget(journalPosition);

    QLineEdit *journalFIO = new QLineEdit();
    journalFIO->setPlaceholderText("фамилия, имя, отчество");
    journalFIO->setFixedWidth(250);
    responsibleLine1->addSpacing(10);
    responsibleLine1->addWidget(journalFIO);

    responsibleLine1->addStretch();
    journalResponsibleBlock->addLayout(responsibleLine1);

    //journalResponsibleBlock->addSpacing(5);

    // Вторая строка (дата)
    QHBoxLayout *responsibleLine2 = new QHBoxLayout();
    responsibleLine2->addStretch();
    responsibleLine2->addWidget(new QLabel("\""));

    QLineEdit *dayField = new QLineEdit();
    dayField->setFixedWidth(30);
    responsibleLine2->addWidget(dayField);

    responsibleLine2->addWidget(new QLabel("\""));

    QLineEdit *monthField = new QLineEdit();
    monthField->setFixedWidth(120);
    responsibleLine2->addWidget(monthField);

    QLineEdit *yearField = new QLineEdit();
    yearField->setFixedWidth(60);
    responsibleLine2->addWidget(yearField);

    responsibleLine2->addWidget(new QLabel("года"));
    responsibleLine2->setAlignment(Qt::AlignRight);

    journalResponsibleBlock->addLayout(responsibleLine2);
    layout1->addLayout(journalResponsibleBlock);


    // Таблица: заголовок + цифры + данные
    QTableWidget *table1 = new QTableWidget(11, 21); // 2 строки заголовка + строка номеров + 10 строк данных
    table1->setFrameShape(QFrame::NoFrame);

    // Верхняя шапка
    table1->setSpan(0, 0, 3, 1);
    QTableWidgetItem *col0 = new QTableWidgetItem("Номер по порядку");
    col0->setTextAlignment(Qt::AlignCenter);
    col0->setFlags(col0->flags() & ~Qt::ItemIsEditable);
    table1->setItem(0, 0, col0);

    table1->setSpan(0, 1, 1, 2);
    QTableWidgetItem *col1 = new QTableWidgetItem("Посуда и приборы");
    col1->setTextAlignment(Qt::AlignCenter);
    col1->setFlags(col1->flags() & ~Qt::ItemIsEditable);
    table1->setItem(0, 1, col1);

    QTableWidgetItem *col1_1 = new QTableWidgetItem("наименование");
    col1_1->setTextAlignment(Qt::AlignCenter);
    col1_1->setFlags(col1_1->flags() & ~Qt::ItemIsEditable);
    table1->setItem(1, 1, col1_1);
    table1->setSpan(1, 1, 2, 1);

    QTableWidgetItem *col2 = new QTableWidgetItem("код");
    col2->setTextAlignment(Qt::AlignCenter);
    col2->setFlags(col2->flags() & ~Qt::ItemIsEditable);
    table1->setItem(1, 2, col2);
    table1->setSpan(1, 2, 2, 1);

    table1->setSpan(0, 3, 1, 2);
    QTableWidgetItem *col3 = new QTableWidgetItem("Единица измерения");
    col3->setTextAlignment(Qt::AlignCenter);
    col3->setFlags(col3->flags() & ~Qt::ItemIsEditable);
    table1->setItem(0, 3, col3);

    QTableWidgetItem *col3_1 = new QTableWidgetItem("наименование");
    col3_1->setTextAlignment(Qt::AlignCenter);
    col3_1->setFlags(col3_1->flags() & ~Qt::ItemIsEditable);
    table1->setItem(1, 3, col3_1);
    table1->setSpan(1, 3, 2, 1);

    QTableWidgetItem *col4 = new QTableWidgetItem("код по ОКЕИ");
    col4->setTextAlignment(Qt::AlignCenter);
    col4->setFlags(col4->flags() & ~Qt::ItemIsEditable);
    table1->setItem(1, 4, col4);
    table1->setSpan(1, 4, 2, 1);

    // Объединённая ячейка ФИО
    table1->setSpan(0, 5, 1, 16);
    QTableWidgetItem *fioHeader = new QTableWidgetItem("Фамилия, имя, отчество");
    fioHeader->setTextAlignment(Qt::AlignCenter);
    fioHeader->setFlags(fioHeader->flags() & ~Qt::ItemIsEditable);
    table1->setItem(0, 5, fioHeader);

    // Строки для ФИО
    for (int i = 0; i < 4; ++i) {
        int start = 5 + i * 4;
        table1->setSpan(1, start, 1, 4);
        table1->setItem(1, start, new QTableWidgetItem(""));
    }

    // Подписи под объединённой ячейкой
    QStringList actions = {"получено", "возвращено", "бой, лом", "недостача"};
    int col = 5;
    for (int group = 0; group < 4; ++group) {
        for (const QString &action : actions) {
            QTableWidgetItem *subHeader = new QTableWidgetItem(action);
            subHeader->setTextAlignment(Qt::AlignCenter);
            subHeader->setFlags(subHeader->flags() & ~Qt::ItemIsEditable);
            table1->setItem(2, col++, subHeader);
        }
    }

    // Строка с нумерацией
    for (int i = 0; i < 21; ++i) {
        QTableWidgetItem *numItem = new QTableWidgetItem(QString::number(i + 1));
        numItem->setTextAlignment(Qt::AlignCenter);
        numItem->setFlags(numItem->flags() & ~Qt::ItemIsEditable); // делаем ячейку нередактируемой
        table1->setItem(3, i, numItem);
    }

    // Строки данных
    for (int r = 4; r < 14; ++r) {
        for (int c = 0; c < 21; ++c) {
            table1->setItem(r, c, new QTableWidgetItem(""));
        }
    }

    // Последняя строка таблицы (итоги и подпись)
    table1->setSpan(10, 0, 1, 5);
    QWidget *footerWidget = new QWidget();
    QHBoxLayout *footerLayout = new QHBoxLayout(footerWidget);
    footerLayout->setContentsMargins(5, 0, 0, 0);
    footerLayout->addWidget(new QLabel("Получено, возвращено, бой, лом, недостача. Подпись:"));
    footerLayout->addWidget(new QLineEdit());
    footerLayout->addStretch();
    table1->setCellWidget(10, 0, footerWidget);

    // Остальные ячейки (6–20) пустые
    for (int c = 5; c < 21; ++c) {
        table1->setItem(13, c, new QTableWidgetItem(""));
    }

    table1->horizontalHeader()->hide();
    table1->verticalHeader()->hide();
    table1->setEditTriggers(QAbstractItemView::AllEditTriggers);
    table1->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //for (int i = 0; i < 21; ++i) table1->setColumnWidth(i, 80);
    //table1->setFixedHeight(450);

    table1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout1->addWidget(table1);

    // Блок: Материально ответственное лицо
    QHBoxLayout *signatureLayout = new QHBoxLayout();

    QLabel *labelMO = new QLabel("Материально ответственное лицо");
    signatureLayout->addWidget(labelMO);

    QLineEdit *linePosition = new QLineEdit();
    linePosition->setPlaceholderText("должность");
    linePosition->setFixedWidth(120);
    signatureLayout->addSpacing(10);
    signatureLayout->addWidget(linePosition);

    QLineEdit *lineSignature = new QLineEdit();
    lineSignature->setPlaceholderText("подпись");
    lineSignature->setFixedWidth(120);
    signatureLayout->addSpacing(10);
    signatureLayout->addWidget(lineSignature);

    QLineEdit *lineDecryption = new QLineEdit();
    lineDecryption->setPlaceholderText("расшифровка подписи");
    lineDecryption->setFixedWidth(180);
    signatureLayout->addSpacing(10);
    signatureLayout->addWidget(lineDecryption);

    signatureLayout->addStretch();
    layout1->addLayout(signatureLayout);

    layout1->addSpacing(15); // отступ перед кнопкой

    QPushButton *saveButton = new QPushButton("Сохранить");
    QPushButton *addRowButton = new QPushButton("Добавить строку");
    QPushButton *closeButton = new QPushButton("Закрыть");

    saveButton->setFixedWidth(150);
    addRowButton->setFixedWidth(150);
    closeButton->setFixedWidth(150);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();  // выравнивание по правому краю
    buttonLayout->addWidget(addRowButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(closeButton);
    layout1->addLayout(buttonLayout);

    // === ВЕРСИЯ 2: Современный интерфейс ===
    QScrollArea *scrollArea = new QScrollArea(modernTab);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollContent = new QWidget();
    scrollArea->setWidget(scrollContent);
    QVBoxLayout *modernLayout = new QVBoxLayout(scrollContent);

    // Заголовок
    QHBoxLayout *modernHeaderLayout = new QHBoxLayout();
    QLabel *iconLabel = new QLabel();
    iconLabel->setPixmap(QPixmap(":/icons/icons/tableware.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    modernHeaderLayout->addWidget(iconLabel);
    QLabel *titleLabel = new QLabel("Журнал учёта столовой посуды");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 18px;");
    modernHeaderLayout->addWidget(titleLabel);
    modernHeaderLayout->addStretch();
    modernLayout->addLayout(modernHeaderLayout);
    modernLayout->addSpacing(10);

    // Основные реквизиты
    QWidget *requisitesContainer = new QWidget();
    QFormLayout *requisitesForm = new QFormLayout(requisitesContainer);
    requisitesForm->addRow("Код формы по ОКУД:", new QLabel("0330519"));
    requisitesForm->addRow("по ОКПО:", new QLineEdit());
    requisitesForm->addRow("Организация:", new QLineEdit());
    requisitesForm->addRow("Структурное подразделение:", new QLineEdit());
    requisitesForm->addRow("Вид деятельности по ОКДП:", new QLineEdit());

    QToolButton *toggleButton = new QToolButton();
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton->setArrowType(Qt::RightArrow);
    toggleButton->setText("Основные реквизиты");
    toggleButton->setCheckable(true);
    toggleButton->setChecked(false);

    connect(toggleButton, &QToolButton::toggled, requisitesContainer, &QWidget::setVisible);
    connect(toggleButton, &QToolButton::toggled, [=](bool checked) {
        toggleButton->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
    });

    requisitesContainer->setVisible(false);  // скрыто по умолчанию

    modernLayout->addWidget(toggleButton);
    modernLayout->addWidget(requisitesContainer);
    modernLayout->addSpacing(10);

    // Период
    QGroupBox *periodBox = new QGroupBox("Период учёта");
    QHBoxLayout *modernPeriodLayout = new QHBoxLayout(periodBox);
    modernPeriodLayout->addWidget(new QLabel("С:"));
    modernPeriodLayout->addWidget(new QLineEdit());
    modernPeriodLayout->addSpacing(20);
    modernPeriodLayout->addWidget(new QLabel("По:"));
    modernPeriodLayout->addWidget(new QLineEdit());
    modernLayout->addWidget(periodBox);

    // Ответственное лицо
    QGroupBox *responsibleBox = new QGroupBox("Ответственное лицо");
    QFormLayout *responsibleLayout = new QFormLayout(responsibleBox);
    responsibleLayout->addRow("Должность:", new QLineEdit());
    responsibleLayout->addRow("ФИО:", new QLineEdit());
    modernLayout->addWidget(responsibleBox);

    // Таблица
    QLabel *tableTitle = new QLabel("Таблица учёта");
    tableTitle->setStyleSheet("font-weight: bold;");
    modernLayout->addWidget(tableTitle);

    QTableWidget *table2 = new QTableWidget(11, 21);
    table2->setFrameShape(QFrame::NoFrame);

    // Шапка
    table2->setSpan(0, 0, 3, 1);
    QTableWidgetItem *m_col0 = new QTableWidgetItem("Номер по порядку");
    m_col0->setTextAlignment(Qt::AlignCenter);
    m_col0->setFlags(m_col0->flags() & ~Qt::ItemIsEditable);
    table2->setItem(0, 0, m_col0);

    table2->setSpan(0, 1, 1, 2);
    QTableWidgetItem *m_col1 = new QTableWidgetItem("Посуда и приборы");
    m_col1->setTextAlignment(Qt::AlignCenter);
    m_col1->setFlags(m_col1->flags() & ~Qt::ItemIsEditable);
    table2->setItem(0, 1, m_col1);

    QTableWidgetItem *m_col1_1 = new QTableWidgetItem("наименование");
    m_col1_1->setTextAlignment(Qt::AlignCenter);
    m_col1_1->setFlags(m_col1_1->flags() & ~Qt::ItemIsEditable);
    table2->setItem(1, 1, m_col1_1);
    table2->setSpan(1, 1, 2, 1);

    QTableWidgetItem *m_col2 = new QTableWidgetItem("код");
    m_col2->setTextAlignment(Qt::AlignCenter);
    m_col2->setFlags(m_col2->flags() & ~Qt::ItemIsEditable);
    table2->setItem(1, 2, m_col2);
    table2->setSpan(1, 2, 2, 1);

    table2->setSpan(0, 3, 1, 2);
    QTableWidgetItem *m_col3 = new QTableWidgetItem("Единица измерения");
    m_col3->setTextAlignment(Qt::AlignCenter);
    m_col3->setFlags(m_col3->flags() & ~Qt::ItemIsEditable);
    table2->setItem(0, 3, m_col3);

    QTableWidgetItem *m_col3_1 = new QTableWidgetItem("наименование");
    m_col3_1->setTextAlignment(Qt::AlignCenter);
    m_col3_1->setFlags(m_col3_1->flags() & ~Qt::ItemIsEditable);
    table2->setItem(1, 3, m_col3_1);
    table2->setSpan(1, 3, 2, 1);

    QTableWidgetItem *m_col4 = new QTableWidgetItem("код по ОКЕИ");
    m_col4->setTextAlignment(Qt::AlignCenter);
    m_col4->setFlags(m_col4->flags() & ~Qt::ItemIsEditable);
    table2->setItem(1, 4, m_col4);
    table2->setSpan(1, 4, 2, 1);

    table2->setSpan(0, 5, 1, 16);
    QTableWidgetItem *m_fioHeader = new QTableWidgetItem("Фамилия, имя, отчество");
    m_fioHeader->setTextAlignment(Qt::AlignCenter);
    m_fioHeader->setFlags(m_fioHeader->flags() & ~Qt::ItemIsEditable);
    table2->setItem(0, 5, m_fioHeader);

    for (int i = 0; i < 4; ++i) {
        int start = 5 + i * 4;
        table2->setSpan(1, start, 1, 4);
        table2->setItem(1, start, new QTableWidgetItem(""));
    }


    QStringList m_actions = {"получено", "возвращено", "бой, лом", "недостача"};
    int m_col = 5;
    for (int group = 0; group < 4; ++group) {
        for (const QString &action : m_actions) {
            QTableWidgetItem *subHeader = new QTableWidgetItem(action);
            subHeader->setTextAlignment(Qt::AlignCenter);
            subHeader->setFlags(subHeader->flags() & ~Qt::ItemIsEditable);
            table2->setItem(2, m_col++, subHeader);
        }
    }

    for (int i = 0; i < 21; ++i) {
        QTableWidgetItem *numItem = new QTableWidgetItem(QString::number(i + 1));
        numItem->setTextAlignment(Qt::AlignCenter);
        numItem->setFlags(numItem->flags() & ~Qt::ItemIsEditable);
        table2->setItem(3, i, numItem);
    }

    for (int r = 4; r < 14; ++r) {
        for (int c = 0; c < 21; ++c) {
            table2->setItem(r, c, new QTableWidgetItem(""));
        }
    }

    table2->setSpan(10, 0, 1, 5);
    QWidget *modernFooterWidget = new QWidget();
    QHBoxLayout *modernFooterLayoutTable = new QHBoxLayout(modernFooterWidget);
    modernFooterLayoutTable->setContentsMargins(5, 0, 0, 0);
    modernFooterLayoutTable->addWidget(new QLabel("Получено, возвращено, бой, лом, недостача. Подпись:"));
    modernFooterLayoutTable->addWidget(new QLineEdit());
    modernFooterLayoutTable->addStretch();
    table2->setCellWidget(10, 0, modernFooterWidget);

    for (int c = 5; c < 21; ++c) {
        table2->setItem(10, c, new QTableWidgetItem(""));
    }

    table2->horizontalHeader()->hide();
    table2->verticalHeader()->hide();
    table2->setEditTriggers(QAbstractItemView::AllEditTriggers);
    table2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    modernLayout->addWidget(table2);

    // Подпись
    QGroupBox *footerBox = new QGroupBox("Материально ответственное лицо");
    QHBoxLayout *modernFooterLayout = new QHBoxLayout(footerBox);
    modernFooterLayout->addWidget(new QLabel("Должность:"));
    modernFooterLayout->addWidget(new QLineEdit());
    modernFooterLayout->addWidget(new QLabel("Подпись:"));
    modernFooterLayout->addWidget(new QLineEdit());
    modernFooterLayout->addWidget(new QLabel("Расшифровка:"));
    modernFooterLayout->addWidget(new QLineEdit());
    modernLayout->addWidget(footerBox);

    // Кнопки
    QHBoxLayout *modernButtonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton(QIcon(":/icons/icons/add.png"), "  Добавить строку");
    QPushButton *saveBtn = new QPushButton(QIcon(":/icons/icons/save.png"), "  Сохранить");
    QPushButton *closeBtn = new QPushButton(QIcon(":/icons/icons/exit.png"), "  Закрыть");
    addBtn->setFixedWidth(160);
    saveBtn->setFixedWidth(160);
    closeBtn->setFixedWidth(160);
    modernButtonLayout->addStretch();
    modernButtonLayout->addWidget(addBtn);
    modernButtonLayout->addSpacing(10);
    modernButtonLayout->addWidget(saveBtn);
    modernButtonLayout->addSpacing(10);
    modernButtonLayout->addWidget(closeBtn);
    modernLayout->addLayout(modernButtonLayout);

    modernTab->setLayout(new QVBoxLayout());
    modernTab->layout()->addWidget(scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
