// The MIT License( MIT )
//
// Copyright( c ) 2020-2021 Scott Aron Bloom
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
// copies of the Softwa , and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "MainWindow.h"

#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QPlainTextEdit>

CMainWindow::CMainWindow( QWidget * parent )
    : QMainWindow( parent )
{

    setObjectName( "MainWindow" );
    resize( 600, 600 );

    auto centralwidget = new QWidget( this );
    auto gridLayout = new QGridLayout( centralwidget );
    
    fAddDir = new QPushButton( centralwidget );
    fAddDir->setText( "Add Directory" );
    gridLayout->addWidget( fAddDir, 0, 0, 1, 1 );

    fAddFile = new QPushButton( centralwidget );
    fAddFile->setText( "Add File" );
    gridLayout->addWidget( fAddFile, 0, 1, 1, 1 );

    auto horizontalSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    gridLayout->addItem( horizontalSpacer, 0, 2, 1, 1 );
    
    fLog = new QPlainTextEdit( centralwidget );
    fLog->setReadOnly( true );
    gridLayout->addWidget( fLog, 1, 0, 1, 3 );
    setCentralWidget( centralwidget );
    setWindowTitle( "File System Watcher Demo" );

    fWatcher = new QFileSystemWatcher( this );
    connect( fWatcher, &QFileSystemWatcher::directoryChanged, this, &CMainWindow::slotDirChanged );
    connect( fWatcher, &QFileSystemWatcher::fileChanged, this, &CMainWindow::slotFileChanged );
    connect( fAddDir, &QPushButton::clicked, this, &CMainWindow::slotAddDir );
    connect( fAddFile, &QPushButton::clicked, this, &CMainWindow::slotAddFile );
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::slotAddDir()
{
    auto path = QFileDialog::getExistingDirectory( this, tr( "Select directory to watch" ) );
    if ( path.isEmpty() )
        return;
    fWatcher->addPath( path );
    dumpWatched();
}

void CMainWindow::slotAddFile()
{
    auto path = QFileDialog::getOpenFileName( this, tr( "Select file to watch" ), QString(), QString( "All Files (*.*)" ) );
    if ( path.isEmpty() )
        return;
    fWatcher->addPath( path );
    dumpWatched();
}

void CMainWindow::dumpWatched()
{
    fLog->appendPlainText( tr( "===============" ) );
    fLog->appendPlainText( tr( "Directories Being Watch" ) );
    fLog->appendPlainText( tr( "===============" ) );
    auto allDirs = fWatcher->directories();
    for( auto && ii : allDirs )
        fLog->appendPlainText( tr( "%1" ).arg( ii ) );

    fLog->appendPlainText( tr( "===============" ) );
    fLog->appendPlainText( tr( "Files Being Watch" ) );
    fLog->appendPlainText( tr( "===============" ) );
    auto allFiles = fWatcher->files();
    for ( auto && ii : allFiles )
        fLog->appendPlainText( tr( "%1" ).arg( ii ) );
}

void CMainWindow::slotDirChanged( const QString & path )
{
    fLog->appendPlainText( tr( "*****Directory Changed: %1\n" ).arg( path ) );
}

void CMainWindow::slotFileChanged( const QString & path )
{
    fLog->appendPlainText( tr( "*****File Changed: %1\n" ).arg( path ) );
}

