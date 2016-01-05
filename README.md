# timehash
TimeHash (thash) ist ein erweiterter Hash-Algorithmus, der von Noscio erfunden und programmiert wurde.
Aus langen MD5 File-Hashes k&ouml;nnen kurze "Public Keys" generiert werden, die anstelle der File-Hashes verwendet werden können.
Zudem wird mit dem Hash auch der aktuelle UNIX-Timestamp verkn&uuml;pft. So kann jederzeit nachvollzogen werden, wann eine Datei fertiggestellt und gehasht wurde.
Dar&uuml;ber hinaus bietet TimeHash auch die M&ouml;glichkeit, mit Hilfe der zus&auml;tzlich generierten "Privat Keys", welche nur dem Hasher der Datei bekannt sind,
sich als Eigent&uuml;mer der Datei validieren.<br>

TimeHash ist als Server-Software in PHP geschrieben und enth&auml;lt 3 Frontend-Skripte ('create.php', 'whois.php' und 'validate.php').<br>
Als Speicherort kann entweder eine MySQL-Datenbank (bei großen Datenmengen aufgrund der h&ouml;heren Effizienz empfohlen) oder eine Datei verwendet eingestellt.<br>
Die Software ist OpenSource und ist auf <a href="https://github.com/jgherb/timehash/">GitHub</a> vertreten.<br>
<br>
Außerdem ist TimeHash als Desktop-Software in C++ geschrieben und enthält die Funktionen, die auch die Standard-Hash-Software unter Linux 'md5sum' beinhaltet.<br>
<br>
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/InteractiveResource" property="dct:title" rel="dct:type">TimeHash</span> von <a xmlns:cc="http://creativecommons.org/ns#" href="http://www.noscio.ml/timehash" property="cc:attributionName" rel="cc:attributionURL">Noscio</a> ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Namensnennung - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.<br />Über diese Lizenz hinausgehende Erlaubnisse können Sie unter <a xmlns:cc="http://creativecommons.org/ns#" href="http://noscio.ml/timehash/license" rel="cc:morePermissions">http://noscio.ml/timehash/license</a> erhalten.
