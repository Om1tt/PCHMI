// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCompleter>
#include <QMap>
#include <QSignalBlocker>
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

    QWidget *paperLikeTab = new QWidget();
    setCentralWidget(paperLikeTab);

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

    // ===== Выпадающий список для ОКДП =====
    QComboBox *okdpBox = new QComboBox();
    okdpBox->setEditable(true);
    QStringList okdpList = {
        "Продукция и услуги сельского хозяйства, охоты и лесоводства",
        "Рыболовство",
        "Горнодобывающая промышленность и разработка карьеров",
        "Обрабатывающая промышленность",
        "Электроэнергия, газ и водоснабжение",
        "Строительство",
        "Оптовая и розничная торговля; ремонт автомобилей, бытовых приборов и предметов личного пользования",
        "Гостиницы и рестораны",
        "Транспорт, складское хозяйство и связь",
        "Финансовое посредничество",
        "Деятельность по операциям с недвижимым имуществом и арендой; деятельность исследовательская и коммерческая",
        "Государственное управление и оборона; обязательное социальное страхование",
        "Образование",
        "Здравоохранение и социальные услуги",
        "Деятельность по предоставлению коммунальных, социальных и персональных услуг прочих",
        "Деятельность по ведению частных домашних хозяйств с наемным обслуживанием",
        "Деятельность экстерриториальных организаций и органов"
    };
    okdpBox->addItem("");
    okdpBox->addItems(okdpList);

    QCompleter *okdpCompleter = new QCompleter(okdpList, this);
    okdpCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    okdpCompleter->setFilterMode(Qt::MatchContains);
    okdpBox->setCompleter(okdpCompleter);
    requisitesLayout->addRow("Вид деятельности по ОКДП:", okdpBox);

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

    QMap<QString, QString> dishes = {
        {"Тарелка", "001"},
        {"Кружка", "002"},
        {"Ложка", "003"},
        {"Вилка", "004"}
    };

    QMap<QString, QString> okei = {
        {"штука", "796"},
        {"набор", "715"},
        {"пара", "778"}
    };

    for (int row = 4; row < 14; ++row) {
        // ===== ПОСУДА — НАИМЕНОВАНИЕ =====
        QComboBox *dishNameBox = new QComboBox();
        dishNameBox->setEditable(true);
        dishNameBox->addItem("");
        dishNameBox->addItems(dishes.keys());
        table1->setCellWidget(row, 1, dishNameBox);

        QCompleter *dishNameCompleter = new QCompleter(dishes.keys(), this);
        dishNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        dishNameCompleter->setFilterMode(Qt::MatchContains);
        dishNameBox->setCompleter(dishNameCompleter);

        // ===== ПОСУДА — КОД =====
        QComboBox *dishCodeBox = new QComboBox();
        dishCodeBox->setEditable(true);
        dishCodeBox->addItem("");
        dishCodeBox->addItems(dishes.values());
        table1->setCellWidget(row, 2, dishCodeBox);

        QCompleter *dishCodeCompleter = new QCompleter(dishes.values(), this);
        dishCodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        dishCodeCompleter->setFilterMode(Qt::MatchContains);
        dishCodeBox->setCompleter(dishCodeCompleter);

        // ===== ЕИ — НАИМЕНОВАНИЕ =====
        QComboBox *unitNameBox = new QComboBox();
        unitNameBox->setEditable(true);
        unitNameBox->addItem("");
        unitNameBox->addItems(okei.keys());
        table1->setCellWidget(row, 3, unitNameBox);

        QCompleter *unitNameCompleter = new QCompleter(okei.keys(), this);
        unitNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        unitNameCompleter->setFilterMode(Qt::MatchContains);
        unitNameBox->setCompleter(unitNameCompleter);

        // ===== ЕИ — КОД ОКЕИ =====
        QComboBox *unitCodeBox = new QComboBox();
        unitCodeBox->setEditable(true);
        unitCodeBox->addItem("");
        unitCodeBox->addItems(okei.values());
        table1->setCellWidget(row, 4, unitCodeBox);

        QCompleter *unitCodeCompleter = new QCompleter(okei.values(), this);
        unitCodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        unitCodeCompleter->setFilterMode(Qt::MatchContains);
        unitCodeBox->setCompleter(unitCodeCompleter);

        // ===== АВТОЗАПОЛНЕНИЕ ПОСУДЫ =====
        connect(dishNameBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(dishCodeBox);
            dishCodeBox->setCurrentText(dishes.value(dishNameBox->currentText(), ""));
        });

        connect(dishCodeBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(dishNameBox);
            dishNameBox->setCurrentText(dishes.key(dishCodeBox->currentText(), ""));
        });

        // ===== АВТОЗАПОЛНЕНИЕ ОКЕИ =====
        connect(unitNameBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(unitCodeBox);
            unitCodeBox->setCurrentText(okei.value(unitNameBox->currentText(), ""));
        });

        connect(unitCodeBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(unitNameBox);
            unitNameBox->setCurrentText(okei.key(unitCodeBox->currentText(), ""));
        });
    }

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

    QPushButton *saveButton = new QPushButton("Сохранить в Excel");
    QPushButton *addRowButton = new QPushButton("Добавить строку");

    connect(addRowButton, &QPushButton::clicked, this, [=]() {
        // Удаляем текущую строку с подписями (если есть)
        int lastRow = table1->rowCount();
        if (table1->cellWidget(lastRow - 1, 0)) {
            table1->removeRow(lastRow - 1);
        }

        // Добавляем новую строку с данными
        int newRow = table1->rowCount();
        table1->insertRow(newRow);

        for (int c = 0; c < 21; ++c) {
            table1->setItem(newRow, c, new QTableWidgetItem(""));
        }

        // === QComboBox ===
        QComboBox *dishNameBox = new QComboBox();
        dishNameBox->setEditable(true);
        dishNameBox->addItem("");
        dishNameBox->addItems(dishes.keys());
        QCompleter *dishNameCompleter = new QCompleter(dishes.keys(), this);
        dishNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        dishNameCompleter->setFilterMode(Qt::MatchContains);
        dishNameBox->setCompleter(dishNameCompleter);
        table1->setCellWidget(newRow, 1, dishNameBox);

        QComboBox *dishCodeBox = new QComboBox();
        dishCodeBox->setEditable(true);
        dishCodeBox->addItem("");
        dishCodeBox->addItems(dishes.values());
        QCompleter *dishCodeCompleter = new QCompleter(dishes.values(), this);
        dishCodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        dishCodeCompleter->setFilterMode(Qt::MatchContains);
        dishCodeBox->setCompleter(dishCodeCompleter);
        table1->setCellWidget(newRow, 2, dishCodeBox);

        QComboBox *unitNameBox = new QComboBox();
        unitNameBox->setEditable(true);
        unitNameBox->addItem("");
        unitNameBox->addItems(okei.keys());
        QCompleter *unitNameCompleter = new QCompleter(okei.keys(), this);
        unitNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        unitNameCompleter->setFilterMode(Qt::MatchContains);
        unitNameBox->setCompleter(unitNameCompleter);
        table1->setCellWidget(newRow, 3, unitNameBox);

        QComboBox *unitCodeBox = new QComboBox();
        unitCodeBox->setEditable(true);
        unitCodeBox->addItem("");
        unitCodeBox->addItems(okei.values());
        QCompleter *unitCodeCompleter = new QCompleter(okei.values(), this);
        unitCodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        unitCodeCompleter->setFilterMode(Qt::MatchContains);
        unitCodeBox->setCompleter(unitCodeCompleter);
        table1->setCellWidget(newRow, 4, unitCodeBox);

        connect(dishNameBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(dishCodeBox);
            dishCodeBox->setCurrentText(dishes.value(dishNameBox->currentText(), ""));
        });
        connect(dishCodeBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(dishNameBox);
            dishNameBox->setCurrentText(dishes.key(dishCodeBox->currentText(), ""));
        });
        connect(unitNameBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(unitCodeBox);
            unitCodeBox->setCurrentText(okei.value(unitNameBox->currentText(), ""));
        });
        connect(unitCodeBox, &QComboBox::currentTextChanged, this, [=]() {
            QSignalBlocker blocker(unitNameBox);
            unitNameBox->setCurrentText(okei.key(unitCodeBox->currentText(), ""));
        });

        // Добавляем строку с подписями в конец
        int footerRow = table1->rowCount();
        table1->insertRow(footerRow);
        table1->setSpan(footerRow, 0, 1, 5);

        QWidget *newFooter = new QWidget();
        QHBoxLayout *footerLayout = new QHBoxLayout(newFooter);
        footerLayout->setContentsMargins(5, 0, 0, 0);
        footerLayout->addWidget(new QLabel("Получено, возвращено, бой, лом, недостача. Подпись:"));
        footerLayout->addWidget(new QLineEdit());
        footerLayout->addStretch();
        table1->setCellWidget(footerRow, 0, newFooter);

        for (int c = 5; c < 21; ++c) {
            table1->setItem(footerRow, c, new QTableWidgetItem(""));
        }
    });

    saveButton->setFixedWidth(150);
    addRowButton->setFixedWidth(150);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();  // выравнивание по правому краю
    buttonLayout->addWidget(addRowButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(saveButton);
    layout1->addLayout(buttonLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
