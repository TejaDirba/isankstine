IŠANKSTINĖ


Šioje programoje yra realizuotos trys funkcijos:

1. Pasikartojančių žodžių skaičiavimas ir pasikartojimų kiekio išvedimas.
2. Cross-reference tipo lentelės sukūrimas naujame faile, kuriame būtų nurodyta, kurioje teksto vietoje (kurioje(-iose) teksto eilutėse) kiekvienas iš daugiau negu vieną kartą pasikartojantis žodis buvo paminėtas.
3. URL nuorodų radimas tekste ir išvedimas į failą.
_____________________________________________________

std::map<std::string, int> (pavadiinta wordCount)
Paskirtis: skaičiuoti, kiek kartų pasikartoja kiekvienas žodis.
Kaip veikia: raktas (key) – žodis (string), reikšmė (value) – kiek kartų jis pasirodė.
Naudoti metodai:
  wordCount[low]++ – jei rakto low dar nėra, automatiškai įterpia su reikšme 0, o tada prideda 1. Taip kaupiamas pasikartojimų skaičius.
  Iteracija per map (pvz., for (auto& p : wordCount)) – kad išvesti tuos žodžius, kurių skaičius > 1.

std::map<std::string, std::set<int>> (pavadinta crossRef)
Paskirtis: sekti, kuriose eilutėse pasirodė kiekvienas žodis.
Kaip veikia: raktas – žodis (string), reikšmė – aibė (set<int>) eilutės numerių, kur žodis pasirodė.
Kodėl std::set<int>? Kad neišsaugotume vieno eilutės numerio du kartus (arba jei žodis kartojosi tame pačiame sakinyje kelis kartus, eilučių numeris vis tiek įrašomas tik vieną sykį).
Naudoti metodai:
  crossRef[low].insert(lineNumber) – jei dar nėra low, sukurs naują įrašą su tuščiu set, paskui įterps eilutės numerį.
  Vėliau iteruojama per crossRef ir, jei wordCount[word] > 1, išvedamas set eilutės numeris.

std::vector<std::string> (pavadinta foundURLs)
Paskirtis: kaupti rastus URL’us iš visų eilučių.
Kaip veikia: kiekvieną kartą radus URL (per regex), jis įdedamas į vektoriaus galą.
Naudoti metodai:
  foundURLs.push_back(url) – prideda rastą URL prie vektoriaus pabaigos.
  Vėliau tiesiog eigoje visi elementai peržvelgiami (for (auto& u : foundURLs)) ir rašomi į urls.txt.
