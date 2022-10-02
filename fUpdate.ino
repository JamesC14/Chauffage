//FONCTION MISE A JOUR DONNEES

void fUpdate(String _val, bool _save){
  String valSearch = "/?prog=";
  int index = _val.indexOf(valSearch) + valSearch.length();
  
  //Mise à jour mode  
  if (_val.indexOf("/?mode=off") != -1) _mode = OFF;
  else if (_val.indexOf("/?mode=on") != -1) _mode = ON;
  else if (_val.indexOf("/?mode=auto") != -1) _mode = AUTO;
  
  //Mise à jour planning
  for (int i = 1; i <= 7; i++){
    for (int j = 0; j <= 23; j++){
      if (_val[index] == '0') prog[i][j] = OFF;
      else if (_val[index] == '1') prog[i][j] = ON;
      else if (_val[index] == '2') prog[i][j] = ECO;
      index++;
    } 
  }
  
  //Sauevagarde données
  if ( (_val.indexOf("&savedata") != -1) && _save){
    Serial.println("Sauvegarde données");
    File file = SPIFFS.open("/data.txt","w");
    file.print(_val);
    file.close();
  }

}
