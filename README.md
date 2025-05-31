IŠANKSTINĖ


Šioje programoje yra realizuotos trys funkcijos:

1. Pasikartojančių žodžių paieška tekste ir pasikartojimų skaičiaus išvedimas į failą (jei pasikartojimų yra daugiau nei 1).
2. Cross-reference lentelės tipo sąrašo išvedimas į failą, kuriame nurodyta, kuriose eilutėse yra pasikartojantys žodžiai.
3. URL nuorodų radimas tekste ir išvedimas į failą.

std::string
Paskirtis: saugoti tekstą (eilutes). Naudojami:
  line – kad nuskaityčiau kiekvieną eilutę iš failo (getline grąžina std::string).
  rawWord, cleaned, low – po žodžių atskyrimo ir apdorojimo.
Naudoti metodai/funkcijos:
  size() / empty() – patikrina žodžio ilgį arba ar jis tuščias.
  substr(start, len) – paima dalį tekstą (naudojama skyrybos ženklams nupjauti).
  operator[] arba at() – tikrinti simbolius (naudojama cleanWord funkcijoje).
  c_str() / data() – (naudojama viduje STL funkcijų, bet apie tai nereikia daug galvoti dabar).

std::map<std::string, int> (pavadiinta wordCount)
Paskirtis: skaičiuoti, kiek kartų pasikartoja kiekvienas žodis.
Kaip veikia: raktas (key) – žodis (string), reikšmė (value) – kiek kartų jis pasirodė.
Naudoti metodai:
  wordCount[low]++ – jei rakto low dar nėra, automatiškai įterpia su reikšme 0, o tada prideda 1. Taip kaupiu pasikartojimų skaičių.
  Iteracija per map (pvz., for (auto& p : wordCount)) – kad išvesti tuos žodžius, kurių skaičius > 1.

std::map<std::string, std::set<int>> (pavadinta crossRef)
Paskirtis: sekti, kuriose eilutėse pasirodė kiekvienas žodis.
Kaip veikia: raktas – žodis (string), reikšmė – aibė (set<int>) eilutės numerių, kur žodis pasirodė.
Kodėl std::set<int>? Kad neišsaugotume vieno eilutės numerio du kartus (arba jei žodis kartojosi tame pačiame sakinyje kelis kartus, eilučių numeris vis tiek įrašomas tik vieną sykį).
Naudoti metodai:
  crossRef[low].insert(lineNumber) – jei low dar nėra žemėlapyje, sukurs naują įrašą su tuščiu set, paskui įterps eilutės numerį.
  Vėliau iteruojama per crossRef ir, jei wordCount[word] > 1, išvedu tą set eilutės numerių.

4. std::vector<std::string> (pavadinta foundURLs)
Paskirtis: kaupti rastus URL’us iš visų eilučių.
Kaip veikia: kiekvienąkart radus URL (per regex), įdedu jį į vektoriaus galą.
Naudoti metodai:
  foundURLs.push_back(url) – prideda rastą URL prie vektoriaus pabaigos.
  Vėliau tiesiog eigoje visi elementai peržvelgiami (for (auto& u : foundURLs)) ir rašomi į urls.txt.

5. std::istringstream
Paskirtis: „skaidyti“ eilutę į „žodžių gabalus“ pagal tarpus (ir kitus whitespace simbolius).
Kaip veikia: sudedu line į istringstream iss(line);, tada su while (iss >> rawWord) imu po vieną fragmentą (t.y. kažkokį gabaliuką iki tarpo).
Kodėl tai patogu: nereikia rašyti savo „split by space“ logikos – tiesiog operator>> paima sekančią „žodžio formą“.
