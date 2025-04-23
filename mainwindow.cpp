// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCompleter>
#include <QMap>
#include <QDir>
#include <QSignalBlocker>
#include <QFormLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollArea>
#include <QSplitter>
#include "libxl.h"
using namespace libxl;

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
    QLineEdit *okpoEdit         = new QLineEdit();
    requisitesLayout->addRow("по ОКПО:", okpoEdit);
    QLineEdit *organizationEdit = new QLineEdit();
    requisitesLayout->addRow("Организация:", organizationEdit);
    QLineEdit *subdivisionEdit  = new QLineEdit();
    requisitesLayout->addRow("Структурное подразделение:", subdivisionEdit);

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

    QHBoxLayout *periodLayout = new QHBoxLayout();
    periodLayout->addStretch();
    periodLayout->addWidget(new QLabel("за период с"));

    QLineEdit *periodFrom = new QLineEdit();
    periodFrom->setFixedWidth(100);
    periodFrom->setPlaceholderText("дата начала");
    periodLayout->addWidget(periodFrom);

    periodLayout->addWidget(new QLabel("по"));

    QLineEdit *periodTo = new QLineEdit();
    periodTo->setFixedWidth(100);
    periodTo->setPlaceholderText("дата конца");
    periodLayout->addWidget(periodTo);

    QLineEdit *periodYear = new QLineEdit();
    periodYear->setFixedWidth(60);
    periodYear->setPlaceholderText("год");
    periodLayout->addWidget(periodYear);

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

    connect(saveButton, &QPushButton::clicked, this, [=]() {
        // 1. Считываем все поля
        QString okpo         = okpoEdit->text();
        QString okdp         = okdpBox->currentText();
        QString organization = organizationEdit->text();
        QString subdivision  = subdivisionEdit->text();

        QString periodFrom, periodTo, periodYear;
        for (QLineEdit *e : paperLikeTab->findChildren<QLineEdit*>()) {
            if (e->placeholderText() == "дата начала") periodFrom = e->text();
            if (e->placeholderText() == "дата конца")  periodTo   = e->text();
            if (e->placeholderText() == "год")         periodYear = e->text();
        }

        QString position    = journalPosition->text();
        QString fio         = journalFIO->text();

        QString day   = dayField  ->text();
        QString month = monthField->text();
        QString year  = yearField ->text();

        QString moPosition   = linePosition  ->text();
        QString moSignature  = lineSignature ->text();
        QString moDecryption = lineDecryption->text();

        // 2. Открываем шаблон
        QString tpl = QCoreApplication::applicationDirPath() + "/template.xlsx";
        if (!QFile::exists(tpl)) {
            QMessageBox::critical(nullptr, "Ошибка", "Шаблон не найден:\n" + tpl);
            return;
        }

        Book* book = xlCreateXMLBook();
        if (!book || !book->load(tpl.toStdWString().c_str())) {
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть шаблон");
            return;
        }
        Sheet* s = book->getSheet(0);
        if (!s) {
            QMessageBox::critical(nullptr, "Ошибка", "Лист не найден в шаблоне");
            book->release();
            return;
        }

        // 3. Запись заголовочных полей
        s->writeStr(5,  68, okpo        .toStdWString().c_str()); // BQ6
        s->writeStr(8,  68, okdp        .toStdWString().c_str()); // BQ9
        s->writeStr(5,   0, organization.toStdWString().c_str()); // A6
        s->writeStr(7,   0, subdivision .toStdWString().c_str()); // A8

        s->writeStr(17, 24, periodFrom .toStdWString().c_str());  // Y18
        s->writeStr(17, 38, periodTo   .toStdWString().c_str());  // AM18
        s->writeStr(17, 51, periodYear .toStdWString().c_str());  // AZ18

        s->writeStr(22, 24, position   .toStdWString().c_str());  // Y23
        s->writeStr(22, 36, fio        .toStdWString().c_str());  // AK23

        s->writeStr(34, 56, day        .toStdWString().c_str());  // BE35
        s->writeStr(34, 58, month      .toStdWString().c_str());  // BG35
        s->writeStr(34, 69, year       .toStdWString().c_str());  // BR35

        s->writeStr(66, 18, moPosition .toStdWString().c_str());  // S67
        s->writeStr(66, 34, moSignature.toStdWString().c_str());  // AI67
        s->writeStr(66, 44, moDecryption.toStdWString().c_str()); // AS67

        // 4. Экспорт номеров по порядку в A44:D63
        const int qtStart  = 4;   // Данные в QTableWidget начинаются с 5-й строки (индекс 4)
        const int exlStart = 43;  // Excel: строка 44 → индекс 43

        for (int r = qtStart; r < table1->rowCount(); ++r) {
            auto *itm = table1->item(r, 0);
            // если ячейки нет или она пустая — выходим
            if (!itm || itm->text().isEmpty()) continue;

            int num    = itm->text().toInt();                          // читаем именно то, что ввёл пользователь
            int exlRow = exlStart + (r - qtStart);

            // пишем этот же номер во все четыре колонки A–D
            for (int c = 0; c < 4; ++c) {
                s->writeNum(exlRow, c, num);
            }
        }

        // 5. Экспорт наименования (E44:N63 — merged region, пишем в E)
        for (int r = qtStart; r < table1->rowCount(); ++r) {
            // читаем из QTableWidget column 1
            QString name;
            if (auto *cb = qobject_cast<QComboBox*>(table1->cellWidget(r, 1))) {
                name = cb->currentText();
            } else if (auto *it = table1->item(r, 1)) {
                name = it->text();
            }
            if (name.isEmpty()) continue;
            int exlRow = exlStart + (r - qtStart);
            s->writeStr(exlRow, 4, name.toStdWString().c_str()); // E = col 4
        }

        // 6. Экспорт кода (O44:Q63 — merged region, пишем в O = col 14)
        for (int r = qtStart; r < table1->rowCount(); ++r) {
            // достаем QComboBox из колонки 2
            auto *cb = qobject_cast<QComboBox*>(table1->cellWidget(r, 2));
            // если виджета нет или текст пустой — выходим
            if (!cb || cb->currentText().isEmpty()) continue;

            QString code = cb->currentText();
            int exlRow   = exlStart + (r - qtStart);

            // вставляем код в колонку O (индекс 14)
            s->writeStr(exlRow, 14, code.toStdWString().c_str());
        }

        // 7. Экспорт единицы измерения (R44:T63 — merged region, пишем в R = col 17)
        for (int r = qtStart; r < table1->rowCount(); ++r) {
            auto *cbUnit = qobject_cast<QComboBox*>(table1->cellWidget(r, 3));
            if (!cbUnit || cbUnit->currentText().isEmpty()) continue;

            QString unitName = cbUnit->currentText();
            int exlRow = exlStart + (r - qtStart);

            // пишем наименование единицы измерения в колонку R (индекс 17)
            s->writeStr(exlRow, 17, unitName.toStdWString().c_str());
        }

        // 8. Экспорт кода по ОКЕИ (U44:X63 — merged region, пишем в U = col 20)
        for (int r = qtStart; r < table1->rowCount(); ++r) {
            auto *cbCodeOKEI = qobject_cast<QComboBox*>(table1->cellWidget(r, 4));
            if (!cbCodeOKEI || cbCodeOKEI->currentText().isEmpty()) continue;

            QString codeOKEI = cbCodeOKEI->currentText();
            int exlRow = exlStart + (r - qtStart);

            // пишем код ОКЕИ в колонку U (индекс 20)
            s->writeStr(exlRow, 20, codeOKEI.toStdWString().c_str());
        }

        // 9. Экспорт «получено» (Y44:AA63 → merged, пишем только в Y = col 24)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 5);  // столбец 5 — «получено»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 24, val);
        }

        // 10. Экспорт «возвращено» (AB44:AE63 → merged, пишем только в AB = col 27)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 6);  // столбец 6 — «возвращено»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 27, val);
        }

        // 11. Экспорт «бой, лом» (AF44:AH63 → merged, пишем только в AF = col 31)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 7);  // столбец 7 — «бой, лом»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 31, val);
        }

        // 12. Экспорт «недостача» (AI44:AK63 → merged, пишем только в AI = col 34)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 8);  // столбец 8 — «недостача»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 34, val);
        }

        // 13. Экспорт «получено» (AL44:AN63 → merged, пишем только в AL = col 37)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 9);  // столбец 9 — второе «получено»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 37, val);
        }

        // 14. Экспорт «возвращено» (AO44:AR63 → merged, пишем только в AO = col 40)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 10); // столбец 10 — второе «возвращено»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 40, val);
        }

        // 15. Экспорт «бой, лом» (AS44:AU63 → merged, пишем только в AS = col 44)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 11); // столбец 11 — второе «бой, лом»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 44, val);
        }

        // 16. Экспорт «недостача» (AV44:AX63 → merged, пишем только в AV = col 47)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 12); // столбец 12 — второе «недостача»
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 47, val);
        }

        // 17. Экспорт «получено» третьей группы (AY44:BA63 → пишем в AY = col 50)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 13);    // третья группа «получено» в table1 — столбец 13
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 50, val);
        }

        // 18. Экспорт «возвращено» третьей группы (BB44:BE63 → колонки BB:BE, пишем в BB = col 53)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 14);    // третья группа «возвращено» — столбец 14
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 53, val);
        }

        // 19. Экспорт «бой, лом» третьей группы (BF44:BH63 → BF = col 57)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 15);    // третья группа «бой, лом» — столбец 15
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 57, val);
        }

        // 20. Экспорт «недостача» третьей группы (BI44:BK63 → BI = col 60)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 16);    // третья группа «недостача» — столбец 16
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 60, val);
        }

        // 21. Экспорт «получено» четвёртой группы (BL44:BN63 → BL = col 63)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 17);    // 4-я группа «получено» в table1 — столбец 17
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 63, val);
        }

        // 22. Экспорт «возвращено» четвёртой группы (BO44:BR63 → BO = col 66)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 18);    // 4-я группа «возвращено» — столбец 18
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 66, val);
        }

        // 23. Экспорт «бой, лом» четвёртой группы (BS44:BU63 → BS = col 70)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 19);    // 4-я группа «бой, лом» — столбец 19
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 70, val);
        }

        // 24. Экспорт «недостача» четвёртой группы (BV44:BX63 → BV = col 73)
        for(int r = qtStart; r < table1->rowCount(); ++r) {
            auto *it = table1->item(r, 20);    // 4-я группа «недостача» — столбец 20
            if(!it || it->text().isEmpty()) continue;
            int val    = it->text().toInt();
            int exlRow = exlStart + (r - qtStart);
            s->writeNum(exlRow, 73, val);
        }

        // --- экспорт последней «строки итогов» ---
        // qtFooterRow — индекс последней строки QTableWidget (где вводятся «Получено, возвращено, бой, лом, недостача. Подпись»)
        int qtFooterRow = table1->rowCount() - 1;

        // в Excel:
        //   строка 64 → индекс 63 (числовые «Получено…»)
        //   строка 65 → индекс 64 (текст подписи)
        const int exlValuesRow = 63;
        const int exlSignRow   = 64;

        // карта: колонка в table1 → колонка в Excel
        std::vector<std::pair<int,int>> footerMap = {
            {5,  24}, {6,  27}, {7,  31}, {8,  34},   // 1-я группа
            {9,  37}, {10, 40}, {11, 44}, {12, 47},   // 2-я группа
            {13, 50}, {14, 53}, {15, 57}, {16, 60},   // 3-я группа
            {17, 63}, {18, 66}, {19, 70}, {20, 73}    // 4-я группа
        };

        // экспортим все четыре «Получено…» из footerRow в Y64:BX64 (индексы по карте)
        for (auto [qtCol, exlCol] : footerMap) {
            if (auto *it = table1->item(qtFooterRow, qtCol)) {
                if (!it->text().isEmpty()) {
                    s->writeNum(exlValuesRow, exlCol, it->text().toDouble());
                }
            }
        }

        // экспорт подписи из QLineEdit в объединённую ячейку A65:X65 (A65 = row 64, col 0)
        if (auto *fw = table1->cellWidget(qtFooterRow, 0)) {
            if (auto *le = fw->findChild<QLineEdit*>()) {
                QString sign = le->text();
                if (!sign.isEmpty()) {
                    s->writeStr(exlSignRow, 0, sign.toStdWString().c_str());
                }
            }
        }

        // 5. Сохраняем результат
        QString savePath = QDir(QCoreApplication::applicationDirPath())
                               .absoluteFilePath("../filled.xlsx");
        if (book->save(savePath.toStdWString().c_str())) {
            QMessageBox::information(nullptr, "Успешно", "Сохранено:\n" + savePath);
        } else {
            QMessageBox::warning(nullptr, "Ошибка", "Не удалось сохранить:\n" + savePath);
        }
        book->release();
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
