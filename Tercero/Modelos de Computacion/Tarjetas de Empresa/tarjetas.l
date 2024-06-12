
%{
  #include<iostream>
  #include<fstream>

  using namespace std;

  ifstream fichero;
  string nom_emp = "";
  string desc = "";
  string num_telf = "";
  string correo = "";
  string pagina_web = "";
  string error = "ERROR: El dato introducido no corresponde con ninguna expresión. \n";
  string revisa = "NO SE PUDO GENERAR TARJETA DE EMPRESA \n";
  int contador = 1;

  void GenerarArchivo(string nombre, string desc, string numero, string correo, string pagina)
  {
    ofstream archivo;

    string nombre_archivo = nombre + ".html";

    archivo.open(nombre_archivo);

    // Generación del archivo html BASTANTE hardcodeado pero funcional y simple

    string cad = "<!DOCTYPE html>\n"
                  "<html>\n"
                  "\n"
                  "<head>\n"
                  "<link rel=\"stylesheet\" href=\"style.css\">\n"
                  "</head>\n"
                  "\n"
                  "<body>\n"
                  "    <div class=\"front-side\">\n"
                  "        <div class=\"color-grid\">\n"
                  "            <div class=\"black\"></div>\n"
                  "            <div class=\"red1\"></div>\n"
                  "            <div class=\"red2\"></div>\n"
                  "            <div class=\"green\"></div>\n"
                  "        </div>\n"
                  "        <div class=\"info-grid\">\n"
                  "            <div class=\"name\">\n"
                  "                <h2>";

    cad+=nombre;

    cad+="</h2>\n"
                  "                <h5>";
    cad+=desc;
    cad+="</h5>\n"
         "        </div>\n"
         "            <div class=\"phoneNo\">\n"
         "                <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" viewBox=\"0 0 472.811 472.811\"\n"
         "                    enable-background=\"new 0 0 472.811 472.811\" width=\"30px\" height=\"30px\">\n"
         "                    <g>\n"
         "                        <path d=\"M358.75,0H114.061C97.555,0,84.128,13.428,84.128,29.934v412.944c0,16.505,13.428,29.934,29.934,29.934H358.75   c16.506,0,29.934-13.428,29.934-29.934V29.934C388.683,13.428,375.256,0,358.75,0z M99.128,75.236h274.556v312.687H99.128V75.236z    M114.061,15H358.75c8.234,0,14.934,6.699,14.934,14.934v35.302H99.128V29.934C99.128,21.699,105.827,15,114.061,15z    M358.75,457.811H114.061c-8.234,0-14.934-6.699-14.934-14.934v-44.955h274.556v44.955   C373.683,451.112,366.984,457.811,358.75,457.811z\"\n"
         "                            fill=\"#FFFFFF\" />\n"
         "                        <path d=\"m236.406,404.552c-13.545,0-24.564,11.02-24.564,24.565s11.02,24.564 24.564,24.564 24.564-11.02 24.564-24.564-11.019-24.565-24.564-24.565zm0,39.129c-8.031,0-14.564-6.534-14.564-14.564 0-8.031 6.533-14.565 14.564-14.565s14.564,6.534 14.564,14.565c0,8.03-6.533,14.564-14.564,14.564z\"\n"
         "                            fill=\"#FFFFFF\" />\n"
         "                        <path d=\"m202.406,47.645h68c2.762,0 5-2.239 5-5s-2.238-5-5-5h-68c-2.762,0-5,2.239-5,5s2.238,5 5,5z\" fill=\"#FFFFFF\" />\n"
         "                        <path d=\"m184.409,47.645c1.31,0 2.6-0.53 3.53-1.46 0.93-0.94 1.47-2.22 1.47-3.54s-0.54-2.6-1.47-3.54c-0.931-0.93-2.221-1.46-3.53-1.46-1.32,0-2.601,0.53-3.54,1.46-0.93,0.93-1.46,2.22-1.46,3.54s0.53,2.6 1.46,3.54c0.93,0.93 2.22,1.46 3.54,1.46z\"\n"
         "                            fill=\"#FFFFFF\" />\n"
         "                    </g>\n"
         "                </svg>\n"
         "                <p>";

    cad+="+34";

    cad+="\n"
         "                    <strong>";

    cad+=numero;

    cad+="</strong> </p>\n"
         "            </div>\n"
         "            <div class=\"emailId\">\n"
         "                <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" viewBox=\"0 0 467.211 467.211\"\n"
         "                    enable-background=\"new 0 0 467.211 467.211\" width=\"30px\" height=\"30px\">\n"
         "                    <g>\n"
         "                        <path d=\"m413.917,96.775h-360.622c-6.369,0-11.551,5.181-11.551,11.55v213.182c0,6.369 5.182,11.55 11.551,11.55h360.622c6.368,0 11.55-5.181 11.55-11.55v-213.181c-5.68434e-14-6.369-5.182-11.551-11.55-11.551zm1.55,224.732c0,0.855-0.695,1.55-1.55,1.55h-360.622c-0.855,0-1.551-0.696-1.551-1.55v-213.181c0-0.855 0.695-1.55 1.551-1.55h360.622c0.854,0 1.55,0.696 1.55,1.55v213.181z\"\n"
         "                            fill=\"#FFFFFF\" />\n"
         "                        <path d=\"m459.711,340.558h-11.744v-237.715c0-15.752-12.815-28.568-28.568-28.568h-371.586c-15.753,0-28.568,12.815-28.568,28.568v237.714h-11.745c-4.143,0-7.5,3.358-7.5,7.5v20.605c0,13.384 10.889,24.272 24.272,24.272h418.666c13.384,0 24.272-10.889 24.272-24.272v-20.605c0.001-4.141-3.356-7.499-7.499-7.499zm-425.467-237.715c-2.84217e-14-7.481 6.087-13.568 13.568-13.568h371.586c7.481,0 13.568,6.086 13.568,13.568v237.714h-398.722v-237.714zm177.361,252.715h44v3.922c0,1.755-1.428,3.184-3.184,3.184h-37.633c-1.756,0-3.184-1.428-3.184-3.184v-3.922zm240.607,13.105c0,5.113-4.159,9.272-9.272,9.272h-418.667c-5.113,0-9.272-4.16-9.272-9.272v-13.105h11.744 174.861v3.922c0,7.27 5.914,13.184 13.184,13.184h37.633c7.27,0 13.184-5.914 13.184-13.184v-3.922h174.861 11.744v13.105z\"\n"
         "                            fill=\"#FFFFFF\" />\n"
         "                    </g>\n"
         "                </svg>\n"
         "                <p class=\"email\">";

    cad+=correo;

    cad+="</p>\n"
         "                <p class=\"web\">";

    cad+=pagina;

    cad+="\n"
         "                </p>\n"
         "            </div>\n"
         "        </div>\n"
         "    </div>\n"
         "    <div class=\"back-side\">\n"
         "        <div class=\"color-grid\">\n"
         "            <div class=\"black\"></div>\n"
         "            <div class=\"red1\"></div>\n"
         "            <div class=\"red2\"></div>\n"
         "            <div class=\"green\"></div>\n"
         "        </div>\n"
         "        <div class=\"name-tag\">\n"
         "            <h1>\n"
         "                <strong>";

    cad+=nombre;

    cad+="</strong>\n"
         "            </h1>\n"
         "            <h3>";
    cad+=desc;
    cad+="</h3>\n"
         "        </div>\n"
         "    </div>\n"
         "\n"
         "\n"
         "</body>";

    archivo << cad;

    archivo.close();
  }

  void GenerarCarta()
  {
    ofstream archivo;

    string nombre_archivo = "style.css";

    archivo.open(nombre_archivo);

    string cad = "html {\n"
                 "  font-size: 17px;\n"
                 "  color: rgb(255, 255, 255);\n"
                 "  font-family: 'Heebo', sans-serif;\n"
                 "  /* font-family: \"Source Sans Pro\", sans-serif; */\n"
                 "  background-color: #ffffff;\n"
                 "}\n"
                 ".front-side,\n"
                 ".back-side {\n"
                 "  width: 390px;\n"
                 "  height: 220px;\n"
                 "  display: grid;\n"
                 "  grid-template-columns: 2% 96% 2%;\n"
                 "  grid-template-rows: 4% 92% 4%;\n"
                 "  position: relative;\n"
                 "  margin: 20px auto;\n"
                 "  overflow: hidden;\n"
                 "  box-shadow: 2px 5px 15px 0px #17161694;\n"
                 "  background-color: #122529;\n"
                 "}\n"
                 ".color-grid {\n"
                 "  display: grid;\n"
                 "  grid-template-columns: repeat(3, 150px);\n"
                 "  grid-template-rows: repeat(8, 50px);\n"
                 "  grid-gap: 8px;\n"
                 "  width: 150px;\n"
                 "  height: 400px;\n"
                 "  transform: rotate(-45deg);\n"
                 "}\n"
                 ".black {\n"
                 "  background-color: #343536;\n"
                 "  grid-column: 2 / span 2;\n"
                 "  grid-row: 1 / span 3;\n"
                 "}\n"
                 ".red1 {\n"
                 "  background-color: #e45e4f;\n"
                 "  grid-row: 2 / span 5;\n"
                 "}\n"
                 ".red2 {\n"
                 "  background-color: #e45e4f;\n"
                 "  grid-column: 2 / span 2;\n"
                 "  grid-row: 4/7;\n"
                 "}\n"
                 ".green {\n"
                 "  background-color: #007e67;\n"
                 "  grid-column: 2/4;\n"
                 "  grid-row: 7/9;\n"
                 "}\n"
                 "\n"
                 ".info-grid {\n"
                 "  grid-column: 2/3;\n"
                 "  grid-row: 2/3;\n"
                 "  z-index: 2;\n"
                 "  width: 100%;\n"
                 "  height: 100%;\n"
                 "  background-color: rgba(255, 255, 255, 0.363);\n"
                 "  box-shadow: 0px 2px 15px rgba(0, 0, 0, 0.432);\n"
                 "  border-radius: 6px;\n"
                 "  font-size: 0.7rem; /*12px;*/\n"
                 "  display: grid;\n"
                 "  grid-template-columns: 15px repeat(3, 1fr) 15px;\n"
                 "  grid-template-rows: repeat(3, 1fr);\n"
                 "  line-height: 1px;\n"
                 "}\n"
                 ".info-grid .name {\n"
                 "  grid-column: 2 / span 2;\n"
                 "  grid-row: 1 / span 1;\n"
                 "  font-size: 1.2em;\n"
                 "  letter-spacing: .1rem;\n"
                 "  margin-top: 8px;\n"
                 "}\n"
                 ".info-grid .name h5{\n"
                 "  font-weight: unset;\n"
                 "}\n"
                 ".info-grid .addr {\n"
                 "  grid-column: 2 / span 2;\n"
                 "  grid-row: 3;\n"
                 "}\n"
                 "\n"
                 ".info-grid .phoneNo {\n"
                 "  grid-column: 3 / span 2;\n"
                 "  grid-row: 2;\n"
                 "  text-align: end;\n"
                 "}\n"
                 ".info-grid .emailId {\n"
                 "  grid-column: 3 / span 2;\n"
                 "  grid-row: 3;\n"
                 "  text-align: end;\n"
                 "  font-size: 1.1em;\n"
                 "}\n"
                 "\n"
                 ".back-side .name-tag {\n"
                 "  grid-column: 1 / span 4;\n"
                 "  grid-row: 2 / span 1;\n"
                 "  align-self: center;\n"
                 "  z-index: 2;\n"
                 "  width: 100%;\n"
                 "  height: 40%;\n"
                 "  display: flex;\n"
                 "  flex-direction: column;\n"
                 "  justify-content: center;\n"
                 "  background-color: rgba(255, 255, 255, 0.363);\n"
                 "  box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.288);\n"
                 "  font-size: 0.6rem; /*12px;*/\n"
                 "  letter-spacing: .1rem;\n"
                 "  text-align: center;\n"
                 "}\n"
                 ".name-tag h1,h3{\n"
                 "  margin: 2px;\n"
                 "  font-weight: unset;\n"
                 "}\n"
                 ".credits{\n"
                 "  margin-top:40px;\n"
                 "  text-align: center;\n"
                 "  color: #343536;\n"
                 "}";

    archivo << cad;

    archivo.close();
  }

%}

%option noyywrap
CUALQUIER_PALABRA   (.)*
TABULADOR           (\t)+
NOMBRE_EMPRESA      [A-Za-z]([A-Za-z0-9]|" ")*
DESCRIPCION         [A-Z]([a-z]|" "[A-Za-z])*
NUMERO_TELEFONO     [6-9]([0-9]{8})
CORREO_ELECTRONICO  [a-z]([a-z0-9]|\.)*@[a-z]([a-z0-9]|\.)*\.[a-z]+
PAGINA_WEB          (www\.|http[s]?:\/\/)[a-z]([\.]?[a-z0-9])*\.[a-z]+[\/]? 
LINEA               {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}

FALLA_EMPRESA       {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_NUMERO        {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_CORREO        {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_WEB           {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_DESCRIPCION   {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}

FALLA_EMPRESA_NUMERO     {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_EMPRESA_CORREO     {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_EMPRESA_WEB        {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_NUMERO_CORREO      {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_NUMERO_WEB         {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_CORREO_WEB         {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_DESC_EMPRESA         {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_DESC_NUMERO         {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_DESC_CORREO         {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_DESC_WEB            {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}

FALLA_EMPRESA_DESC_NUMERO       {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{PAGINA_WEB}
FALLA_EMPRESA_DESC_CORREO       {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_EMPRESA_DESC_WEB          {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_EMPRESA_NUMERO_CORREO     {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_EMPRESA_NUMERO_WEB        {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_EMPRESA_CORREO_WEB        {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_DESC_NUMERO_CORREO        {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}
FALLA_DESC_NUMERO_WEB           {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_DESC_CORREO_WEB           {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
FALLA_NUMERO_CORREO_WEB         {NOMBRE_EMPRESA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}

NO_FALLA_EMPRESA  {NOMBRE_EMPRESA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
NO_FALLA_DESC     {CUALQUIER_PALABRA}{TABULADOR}{DESCRIPCION}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
NO_FALLA_NUMERO   {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{NUMERO_TELEFONO}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}
NO_FALLA_CORREO   {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CORREO_ELECTRONICO}{TABULADOR}{CUALQUIER_PALABRA}
NO_FALLA_WEB      {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{PAGINA_WEB}


FALLA_TODO      {CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}{TABULADOR}{CUALQUIER_PALABRA}

%%
{NOMBRE_EMPRESA}  {
        cout << "Nombre correcto: ";
        for(int i = 0; i < yyleng; i++){
          cout << yytext[i];
        }
        cout << endl;
}
{NUMERO_TELEFONO} {
        cout << "Número de teléfono correcto: ";
        for(int i = 0; i < yyleng; i++){
          cout << yytext[i];
        }
        cout << endl;
}
{CORREO_ELECTRONICO}  {
        cout << "Correo electrónico correcto: ";
        for(int i = 0; i < yyleng; i++){
          cout << yytext[i];
        }
        cout << endl;
}
{PAGINA_WEB}  {
        cout << "Página web correcta: ";
        for(int i = 0; i < yyleng; i++){
          cout << yytext[i];
        }
        cout << endl;
}


\t {}
\n {}

{LINEA} {
        int i = 0;
        while(yytext[i] != '\t'){
          nom_emp += yytext[i];
          i++;
        }
        while(yytext[i] == '\t') i++;
        while(yytext[i] != '\t'){
          desc += yytext[i];
          i++;
        }
        while(yytext[i] == '\t') i++;
        while(yytext[i] != '\t'){
          num_telf += yytext[i];
          i++;
        }
        while(yytext[i] == '\t') i++;
        while(yytext[i] != '\t'){
          correo += yytext[i];
          i++;
        }
        while(yytext[i] == '\t') i++;
        while(i < yyleng){
          pagina_web += yytext[i];
          i++;
        }
        GenerarArchivo(nom_emp, desc, num_telf, correo, pagina_web);
        nom_emp = "";
        num_telf = "";
        correo = "";
        pagina_web = "";
        desc = "";

        contador++;

}

{FALLA_EMPRESA} {

        cout << "EMPRESA INCORRECTA: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_NUMERO} {

        cout << "NUMERO INCORRECTO: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}

{FALLA_CORREO} {

        cout << "CORREO INCORRECTO: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_WEB} {

        cout << "WEB INCORRECTA: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_DESCRIPCION} {
        cout << "DESCRIPCIÓN: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_EMPRESA_NUMERO} {

        cout << "EMPRESA Y NUMERO INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_DESC_EMPRESA} {

        cout << "EMPRESA Y DESCRIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}
{FALLA_DESC_NUMERO} {

        cout << "TELÉFONO Y DESCRIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}
{FALLA_DESC_CORREO} {

        cout << "CORREO Y DESCRIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}
{FALLA_DESC_WEB} {

        cout << "WEB Y DESCRIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}

{FALLA_EMPRESA_CORREO} {

        cout << "EMPRESA Y CORREO INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;

}

{FALLA_EMPRESA_WEB} {

        cout << "EMPRESA Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_NUMERO_CORREO} {

        cout << "NUMERO Y CORREO INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_NUMERO_WEB} {

        cout << "NUMERO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_CORREO_WEB} {

        cout << "CORREO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_EMPRESA_NUMERO_CORREO} {

        cout << "EMPRESA, NUMERO Y CORREO INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_EMPRESA_NUMERO_WEB} {

        cout << "EMPRESA, NUMERO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_EMPRESA_CORREO_WEB} {

        cout << "EMPRESA, CORREO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_NUMERO_CORREO_WEB} {

        cout << "NUMERO, CORREO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_EMPRESA_DESC_NUMERO} {
        cout << "NOMBRE, DESCRIPCIÓN Y NÚMERO INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{FALLA_EMPRESA_DESC_CORREO} {
        cout << "NOMBRE, CORREO Y DESCIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{FALLA_EMPRESA_DESC_WEB} {
        cout << "NOMBRE, DESCRIPCIÓN Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{FALLA_DESC_NUMERO_CORREO} {
        cout << "NUMERO, CORREO Y DESCRIPCIÓN INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{FALLA_DESC_NUMERO_WEB} {
        cout << "NUMERO, DESCRIPCION Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{FALLA_DESC_CORREO_WEB} {
        cout << "DESCRIPCIÓN, CORREO Y WEB INCORRECTOS: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{NO_FALLA_EMPRESA}  {
        cout << "TODOS LOS DATOS SON INCORRECTOS EXCEPTO EL NOMBRE: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{NO_FALLA_DESC}  {
        cout << "TODOS LOS DATOS SON INCORRECTOS EXCEPTO LA DESCRIPCIÓN: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{NO_FALLA_NUMERO}  {
        cout << "TODOS LOS DATOS SON INCORRECTOS EXCEPTO EL NUMERO DE TELEFONO: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{NO_FALLA_CORREO}  {
        cout << "TODOS LOS DATOS SON INCORRECTOS EXCEPTO EL CORREO ELECTRÓNICO: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}
{NO_FALLA_WEB}  {
        cout << "TODOS LOS DATOS SON INCORRECTOS EXCEPTO LA PÁGINA WEB: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

{FALLA_TODO} {

        cout << "TODO INCORRECTO: NO SE HA GENERADO LA TARJETA ASOCIADA A LA ENTRADA " 
             << contador << " DEL FICHERO" << endl;
             contador++;
}

. { cout << error << revisa; }

%%

int main (int argc, char *argv[]){
  if(argc == 2){
    fichero.open(argv[1]);
    
    if(!fichero){
      cout << "ERROR: El documento no se ha podido leer.\n";
      exit(1);
    }
  }
  else{
    cout << "ERROR: No se han introducido los argumentos correctamente.\n";
    exit(1);
  }

  GenerarCarta();
  yyFlexLexer flujo (&fichero,0);
  flujo.yylex();
    
  return 0;
}

