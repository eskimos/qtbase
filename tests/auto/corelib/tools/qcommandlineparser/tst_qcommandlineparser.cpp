/****************************************************************************
**
** Copyright (C) 2013 David Faure <faure+bluesystems@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtCore/QCommandLineParser>

Q_DECLARE_METATYPE(char**)

class tst_QCommandLineParser : public QObject
{
    Q_OBJECT

private slots:
    void testRemainingArguments();
    void testBooleanOption_data();
    void testBooleanOption();
    void testMultipleNames_data();
    void testMultipleNames();
    void testSingleValueOption_data();
    void testSingleValueOption();
    void testValueNotSet();
    void testMultipleValuesOption();
    void testUnknownOptionErrorHandling();
    void testProcessNotCalled();
};

static char *empty_argv[] = { const_cast<char*>("tst_qcommandlineparser") };
static int empty_argc = 1;

void tst_QCommandLineParser::testRemainingArguments()
{
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineParser parser;
    parser.parse(QStringList() << "tst_qcommandlineparser" << "file.txt");
    QCOMPARE(parser.remainingArguments(), QStringList() << QStringLiteral("file.txt"));
}

void tst_QCommandLineParser::testBooleanOption_data()
{
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<QStringList>("expectedOptionNames");
    QTest::addColumn<bool>("expectedIsSet");

    QTest::newRow("set") << (QStringList() << "tst_qcommandlineparser" << "-b") << (QStringList() << "b") << true;
    QTest::newRow("unset") << (QStringList() << "tst_qcommandlineparser") << QStringList() << false;
}

void tst_QCommandLineParser::testBooleanOption()
{
    QFETCH(QStringList, args);
    QFETCH(QStringList, expectedOptionNames);
    QFETCH(bool, expectedIsSet);
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineParser parser;
    QVERIFY(parser.addOption(QCommandLineOption(QStringList() << "b", QStringLiteral("a boolean option"))));
    parser.parse(args);
    QCOMPARE(parser.optionNames(), expectedOptionNames);
    QCOMPARE(parser.isSet("b"), expectedIsSet);
    QCOMPARE(parser.arguments("b"), QStringList());
    QCOMPARE(parser.remainingArguments(), QStringList());
}

void tst_QCommandLineParser::testMultipleNames_data()
{
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<QStringList>("expectedOptionNames");

    QTest::newRow("short") << (QStringList() << "tst_qcommandlineparser" << "-v") << (QStringList() << "v");
    QTest::newRow("long") << (QStringList() << "tst_qcommandlineparser" << "--version") << (QStringList() << "version");
}

void tst_QCommandLineParser::testMultipleNames()
{
    QFETCH(QStringList, args);
    QFETCH(QStringList, expectedOptionNames);
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineOption option(QStringList() << "v" << "version", QStringLiteral("Show version information"));
    QCOMPARE(option.names(), QStringList() << "v" << "version");
    QCommandLineParser parser;
    QVERIFY(parser.addOption(option));
    parser.parse(args);
    QCOMPARE(parser.optionNames(), expectedOptionNames);
    QVERIFY(parser.isSet("v"));
    QVERIFY(parser.isSet("version"));
}

void tst_QCommandLineParser::testSingleValueOption_data()
{
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<QStringList>("defaults");
    QTest::addColumn<bool>("expectedIsSet");

    QTest::newRow("short") << (QStringList() << "tst" << "-s" << "oxygen") << QStringList() << true;
    QTest::newRow("long") << (QStringList() << "tst" << "--style" << "oxygen") << QStringList() << true;
    QTest::newRow("longequal") << (QStringList() << "tst" << "--style=oxygen") << QStringList() << true;
    QTest::newRow("default") << (QStringList() << "tst") << (QStringList() << "oxygen") << false;
}

void tst_QCommandLineParser::testSingleValueOption()
{
    QFETCH(QStringList, args);
    QFETCH(QStringList, defaults);
    QFETCH(bool, expectedIsSet);
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineParser parser;
    QCommandLineOption option(QStringList() << "s" << "style", QStringLiteral("style name"), QCommandLineOption::OneValue);
    option.setDefaultValues(defaults);
    QVERIFY(parser.addOption(option));
    parser.parse(args);
    QCOMPARE(parser.isSet("s"), expectedIsSet);
    QCOMPARE(parser.isSet("style"), expectedIsSet);
    QCOMPARE(parser.arguments("s"), QStringList() << "oxygen");
    QCOMPARE(parser.arguments("style"), QStringList() << "oxygen");
    QCOMPARE(parser.remainingArguments(), QStringList());
}

void tst_QCommandLineParser::testValueNotSet()
{
    QCoreApplication app(empty_argc, empty_argv);
    // Not set, no default value
    QCommandLineParser parser;
    QCommandLineOption option(QStringList() << "s" << "style", QStringLiteral("style name"));
    option.setOptionType(QCommandLineOption::OneValue);
    QVERIFY(parser.addOption(option));
    parser.parse(QStringList() << "tst");
    QCOMPARE(parser.optionNames(), QStringList());
    QVERIFY(!parser.isSet("s"));
    QVERIFY(!parser.isSet("style"));
    QCOMPARE(parser.arguments("s"), QStringList());
    QCOMPARE(parser.arguments("style"), QStringList());
}

void tst_QCommandLineParser::testMultipleValuesOption()
{
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineOption option(QStringList() << "param", QStringLiteral("Pass parameter to the backend"));
    option.setOptionType(QCommandLineOption::OneValue);
    {
        QCommandLineParser parser;
        QVERIFY(parser.addOption(option));
        parser.parse(QStringList() << "tst" << "--param" << "key1=value1");
        QVERIFY(parser.isSet("param"));
        QCOMPARE(parser.arguments("param"), QStringList() << "key1=value1");
        QCOMPARE(parser.argument("param"), QString("key1=value1"));
    }
    {
        QCommandLineParser parser;
        QVERIFY(parser.addOption(option));
        parser.parse(QStringList() << "tst" << "--param" << "key1=value1" << "--param" << "key2=value2");
        QVERIFY(parser.isSet("param"));
        QCOMPARE(parser.arguments("param"), QStringList() << "key1=value1" << "key2=value2");
        QCOMPARE(parser.argument("param"), QString("key2=value2"));
    }
}

void tst_QCommandLineParser::testUnknownOptionErrorHandling()
{
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineParser parser;
    parser.parse(QStringList() << "tst_qcommandlineparser" << "--foobar");
    QCOMPARE(parser.unknownOptionNames(), QStringList() << "foobar");
}

void tst_QCommandLineParser::testProcessNotCalled()
{
    QCoreApplication app(empty_argc, empty_argv);
    QCommandLineParser parser;
    QVERIFY(parser.addOption(QCommandLineOption(QStringList() << "b", QStringLiteral("a boolean option"))));
    QTest::ignoreMessage(QtWarningMsg, "QCommandLineParser: call process or parse before isSet");
    QVERIFY(!parser.isSet("b"));
    QTest::ignoreMessage(QtWarningMsg, "QCommandLineParser: call process or parse before arguments");
    QCOMPARE(parser.arguments("b"), QStringList());
}

QTEST_APPLESS_MAIN(tst_QCommandLineParser)
#include "tst_qcommandlineparser.moc"
