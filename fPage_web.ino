//FONCTION GENERATION PAGE WEB
String fPage_web(){
//Déclaration des variables
  String PAGEWEB;

//Génération page WEB :
PAGEWEB += "<!DOCTYPE HTML>";
PAGEWEB += "<html>";
  
//HEADER
  PAGEWEB += "<head>";
  PAGEWEB +=  "<meta charset='utf-8' />";
  PAGEWEB +=  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  PAGEWEB +=  "<title>CHAUFFAGE : Chambre Léa</title>";
  PAGEWEB +=  "<link rel='icon' type='image/png' sizes='16x16' href='https://nsa40.casimages.com/img/2021/07/01/21070112422541371.jpg'>"; //https://nsa40.casimages.com/img/2021/06/29//210629010148557539.jpg
  PAGEWEB +=  "<link rel='apple-touch-icon' type='image/png' sizes='16x16' href='https://nsa40.casimages.com/img/2021/07/01/21070112422541371.jpg'>";
  

  //CSS
  PAGEWEB +=  "<style type'text/css'>";
  PAGEWEB +=    "#title {font-family: Calibri; color: white; font-size: 150%; font-weight: bold; text-transform: uppercase;}";
  PAGEWEB +=    "#tab_planning {border-collapse: collapse}";
  PAGEWEB +=    ".cells_planning {border: 0px solid black;font-weight: bold;text-align: center}";
  PAGEWEB +=    ".prog {border: 1px solid black;}";
  PAGEWEB +=    ".fix {width: 20px;}";
  PAGEWEB +=    ".legend_text {font-size: 65%;}";
  PAGEWEB +=    ".legend_color {font-size: 65%; border: 1px solid black;}";
  PAGEWEB +=    ".div_title {margin-left: 1px; margin-right: 1px; margin-top: 1px; background-color: #2196F3; vertical-align:middle;}";
  PAGEWEB +=    ".div_title span{vertical-align:middle; display: table-cell; text-align: center; font-family: Calibri; color: white; font-size: 150%; font-weight: bold; text-transform: uppercase;}";
  PAGEWEB +=    ".div_encadrement {margin-left: 1px; margin-right: 5px; margin-top: 1px; border: 2px solid #333; box-shadow: 3px 3px 1px #444; padding: 8px 12px; background-color: #7b38d8);}";
  PAGEWEB +=    ".switch-field {display: flex; margin-top: 10px; margin-bottom: 10px; margin-left: auto; margin-right: auto; overflow: hidden;}";
  PAGEWEB +=    ".div_planning {overflow: auto;}";
  PAGEWEB +=    ".switch-field input {position: absolute !important; clip: rect(0, 0, 0, 0); height: 1px; width: 1px; border: 0; overflow: hidden;}";
  PAGEWEB +=    ".switch-field label {background-color: #ffffff; color: black; font-weight: bold; font-size: 14px; line-height: 1; text-align: center; padding: 8px 16px; margin-right: -1px; border: 1px solid rgba(0, 0, 0, 0.2); box-shadow: inset 0 1px 3px rgba(0, 0, 0, 0.3), 0 1px rgba(255, 255, 255, 0.1); transition: all 0.1s ease-in-out;}";
  PAGEWEB +=    ".switch-field input:checked + label {background-color: #2196F3; color: white; font-weight: bold; box-shadow: none;}";
  PAGEWEB +=    ".switch-field label:first-of-type {border-radius: 0px 0 0 0px;}";
  PAGEWEB +=    ".switch-field label:last-of-type {border-radius: 0 0px 0px 0;}";
  PAGEWEB +=    "input {background-color: #2196F3; border-radius: 0px; border: 0px; color: #FFFF; text-align: center; font-weight: bold; padding: 6px 20px; margin: 2px 5px; cursor: pointer; text-transform: uppercase; position: relative;}";
  PAGEWEB +=  "</style>";

  PAGEWEB += "</head>";

//BODY
  PAGEWEB += "<body>";

  //TITTLE
  PAGEWEB += "<div class='div_title'>";
  PAGEWEB +=    "<span id='title'>Chauffage connecté</span>";
  PAGEWEB += "</div>";
  PAGEWEB += "<p> </p>";

  //MODE
  PAGEWEB += "<div class='div_encadrement'>";
  PAGEWEB +=    "<div class='switch-field'>";
  PAGEWEB +=      "<input type='radio' id='mode_off' name='mode_select' value='off' ";
    if (_mode == OFF) PAGEWEB += "checked";
  PAGEWEB +=      "/>";
  PAGEWEB +=      "<label for='mode_off'>OFF</label>";
  PAGEWEB +=      "<input type='radio' id='mode_on' name='mode_select' value='on' ";
    if (_mode == ON) PAGEWEB += "checked";
  PAGEWEB +=      "/>";
  PAGEWEB +=      "<label for='mode_on'>ON</label>";
  PAGEWEB +=      "<input type='radio' id='mode_auto' name='mode_select' value='auto' ";
    if (_mode == AUTO) PAGEWEB += "checked";
  PAGEWEB +=      "/>"; 
  PAGEWEB +=      "<label for='mode_auto'>AUTO</label>";
  PAGEWEB +=    "</div>"; 

  //TABLEAU PLANNING
  PAGEWEB +="<div class='div_planning'>";
  PAGEWEB +="<table id='tab_planning'>";
  PAGEWEB +=  "<tr class='cells_planning'>";
  PAGEWEB +=    "<td></td>";
    
    //--> Génération ligne heures
  for (byte i = 0; i <= 23; i++){
    PAGEWEB += "<td id='tab'>";
    if (i == hour) {
      PAGEWEB += "<font color='red'>";
        if (i < 10) PAGEWEB += "0" + String(i);
        else PAGEWEB += String(i);
      PAGEWEB += "</font>";
    }
    else {
      if (i < 10) PAGEWEB += "0" + String(i);
      else PAGEWEB += String(i);
    }
    PAGEWEB += "</td>";
  }
  PAGEWEB +=  "<tr/>";

    //--> Génération lignes jours
  String tab_day[] = {"L", "M", "M", "J", "V", "S", "D"};
  byte index = 0;

  for (byte i = 1; i <= 7; i++){
    PAGEWEB +=  "<tr class='cells_planning'>";
    PAGEWEB +=    "<td class='fix'>";
    if (i == day) {
      PAGEWEB += "<font color='red'>" + tab_day[i-1] + "</font>";
    }
    else {
      PAGEWEB += tab_day[i-1];
    }
    PAGEWEB += "</td>";

    for (byte j = 0; j <= 23; j++){
      String color;
      if (prog[i][j] == OFF) color = "#FFFFFF";
      else if (prog[i][j] == ON) color = "#2196F3";
      else if (prog[i][j] == ECO) color = "#FFFF";
      PAGEWEB += "<td class='prog' style='color:rgba(1,1,1,0);' onclick='color(" + String(index) + ");' bgColor ='" + color + "'id='" + String(index) + "'>00</td>";
      index ++; 
    }
    PAGEWEB +=  "</tr>";
  }
  PAGEWEB +=  "</table></br>";
  
  PAGEWEB +=    "<table id='tab_planning'>";
  PAGEWEB +=    "<tr class='cells_planning'>";
  PAGEWEB +=      "<td class='legend_color' style='color:rgba(1,1,1,0);' bgColor ='#FFFFFF'>00</td>";
  PAGEWEB +=      "<td class='legend_text'> OFF</td>";
  PAGEWEB +=      "<td></td>";
  PAGEWEB +=      "<td class='legend_color' style='color:rgba(1,1,1,0);' bgColor ='#2196F3'>00</td>";
  PAGEWEB +=      "<td class='legend_text'> ON</td>";
  PAGEWEB +=      "<td></td>";
  PAGEWEB +=      "<td class='legend_color' style='color:rgba(1,1,1,0);' bgColor ='#FFFF'>00</td>";
  PAGEWEB +=      "<td class='legend_text'> ECO</td>";
  PAGEWEB +=    "</tr>";
  PAGEWEB +=  "</table></br>";
  PAGEWEB +=  "</div>";

  PAGEWEB +="<a><input type='button' value='Valider' onclick='update_planning();'>";
  PAGEWEB +="<input type='checkbox' id='save_data'><label>Sauvegarder</label>";
  PAGEWEB +="</a>";

  PAGEWEB +="<p>";
  PAGEWEB += dayString[day] + "(" + String(day) + ")" + " : " + timeClient.getFormattedTime() + "</br>";
  PAGEWEB +="Optocoupleur 1 : " + String(digitalRead(RLY1)) + " / Optocoupleur 2 : " + String(digitalRead(RLY2));
  PAGEWEB +="</p>";

//JAVASCRIPT
  PAGEWEB +="<script type='text/javascript'>";

    //FUNCTION COLOR
  PAGEWEB +=  "function color(id_prog){";
  PAGEWEB +=  "var colored = document.getElementById(id_prog).bgColor;";

  PAGEWEB += "if (colored === '#FFFFFF'){";
  PAGEWEB +=    "colored = '#2196F3';";
  PAGEWEB +=    "}";
  PAGEWEB +=  "else if (colored === '#2196F3'){";
  PAGEWEB +=    "colored = '#FFFF';";
  PAGEWEB +=    "}";
  PAGEWEB +=  "else {";
  PAGEWEB +=    "colored = '#FFFFFF';";
  PAGEWEB +=    "}";
  PAGEWEB +=  "document.getElementById(id_prog).bgColor = colored;";
  PAGEWEB +=  "}";

    //FUNCTION UPDATE
  PAGEWEB +=  "function update_planning(){";
  PAGEWEB +=  "var mode = '?mode=';";
  PAGEWEB +=  "var programmation = '/?prog=';";
  PAGEWEB +=  "var data;";

  PAGEWEB +=  "if (document.getElementById('mode_off').checked){";
  PAGEWEB +=    "mode = mode + 'off';";
  PAGEWEB +=  "}";
  PAGEWEB +=  "else if (document.getElementById('mode_on').checked){";
  PAGEWEB +=    "mode = mode + 'on';";
  PAGEWEB +=  "}";
  PAGEWEB +=  "else if (document.getElementById('mode_auto').checked){";
  PAGEWEB +=    "mode = mode + 'auto';";
  PAGEWEB +=  "}";

  PAGEWEB +=  "for (let i = 0; i <= 167; i++) {";
  PAGEWEB +=    "if (document.getElementById(i).bgColor === '#FFFFFF'){";
  PAGEWEB +=    "programmation = programmation + '0';";
  PAGEWEB +=    "}";
  PAGEWEB +=    "else if (document.getElementById(i).bgColor === '#2196F3'){";
  PAGEWEB +=    "programmation = programmation + '1';";
  PAGEWEB +=    "}";
  PAGEWEB +=    "else if (document.getElementById(i).bgColor === '#FFFF'){";
  PAGEWEB +=    "programmation = programmation + '2';";
  PAGEWEB +=    "}";
  PAGEWEB +=  "}";
  
  PAGEWEB +=  "data = mode + programmation + '/&random=' + Math.trunc(Math.random() * 1000000);";
  //PAGEWEB +=  "data = programmation + '&random=' + Math.trunc(Math.random() * 1000000);";
  PAGEWEB +=  "if (document.getElementById('save_data').checked){";
  PAGEWEB +=    "data = data + '&savedata';";
  PAGEWEB +=  "}";
  PAGEWEB +=  "document.location.href = data;";
  PAGEWEB +=  "}";  

  PAGEWEB +="</script>";
  
  PAGEWEB += "</body>";

  PAGEWEB += "</html>";
  
  
  return (PAGEWEB);
}
