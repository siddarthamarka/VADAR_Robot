function doPost(e) {
  var folder = DriveApp.getFolderById("YOUR_FOLDER_ID");
  var blob = e.postData.contents;
  var file = folder.createFile(blob);
  file.setName("Accident_" + new Date().toISOString() + ".jpg");
  return ContentService.createTextOutput("Success");
}
