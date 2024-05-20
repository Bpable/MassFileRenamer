/*-------------------------------------------------------------------------*/
//
//                               Harsco Rail
//                             2401 Edmund Road
//                          West Columbia, SC 29171
//                  Copyright 2014-2024 All Rights Reserved
//
//   Date          : January 1,  2024
//   Filename      : main.cpp
//   Developer(s)  : Brent Able
//   Purpose       : Program to mass rename all data for data labeling
//
//
//
/*-------------------------------------------------------------------------*/
//
//                                 INCLUDES
//
//
#include <QCoreApplication>
#include <QString>
#include <QDir>
#include <QDebug>
/*-------------------------------------------------------------------------*/
//
//   Requires path to base folder, and intended base name for renaming,
//    then to specify if its inner or outer
//
//

//
// Need to modify this file as needed
//
QString path = "/media/bable/BlackBoxRight";

//
// Need to change the date and then O for Outer, I for Inner
//
QString folderFormat = "10_22_TN_2_%1";
QString fileFormat = "10_22_TN_2_%1_%2.JPG";

void renameFiles(const QString &Path)
{
   QDir baseDir(Path);

   if(!baseDir.exists())
   {
      qWarning() << "The base directory does not exist!";
      return;
   }

   QStringList subDirs = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

   int dataSetCount = 1;

   for (const QString &subDir : subDirs) {
      QDir dataSetDir(baseDir.absoluteFilePath(subDir));
      QString setCount = QString::number(dataSetCount).rightJustified(3, '0');

      // Get a list of all files in the subdirectory
      QStringList files = dataSetDir.entryList(QDir::Files);

      // Rename the files in the subdirectory
      int fileCount = 1;
      for (const QString &fileName : files) {
         QString fileCounter = QString::number(fileCount).rightJustified(4, '0');
         // need to adjust the QString part for the date, and inner or outer.
         QString newFileName = QString(fileFormat).arg(setCount).arg(fileCounter);
         if (dataSetDir.rename(fileName, newFileName)) {
            qDebug() << "Renamed:" << dataSetDir.absoluteFilePath(fileName) << "->" << newFileName;
         } else {
            qWarning() << "Failed to rename:" << dataSetDir.absoluteFilePath(fileName);
         }
         fileCount++;
      }

      // Rename the subdirectory
      // same here need to adjust date & inner/outer part
      QString newSubDirName = QString(folderFormat).arg(setCount);
      if (baseDir.rename(subDir, newSubDirName)) {
         qDebug() << "Renamed:" << dataSetDir.path() << "->" << newSubDirName;
      } else {
         qWarning() << "Failed to rename:" << dataSetDir.path();
      }

      dataSetCount++;
   }
}

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   renameFiles(path);

   return a.exec();
}
