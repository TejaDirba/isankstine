#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <regex>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// Funkcija, kurią panaudosime, kad iš žodžio pašalintume skyrybos ženklus (.,;:?! etc.) gale ir pradžioje
string cleanWord(const string& raw) {
    int start = 0;
    int end = (int)raw.size() - 1;
    // pereiname tol, kol randame raidę arba skaičių
    while (start <= end && !isalnum((unsigned char)raw[start])) {
        start++;
    }
    while (end >= start && !isalnum((unsigned char)raw[end])) {
        end--;
    }
    if (start > end) return ""; // reiškia, žodis buvo tik skyrybos ženklai
    return raw.substr(start, end - start + 1);
}

// Funkcija, kuri paverčia visą string į mažąsias raides
string toLowerStr(const string& s) {
    string out = s;
    for (char& c : out) c = (char)tolower((unsigned char)c);
    return out;
}

int main() {
    const string INPUT_FILE = "input.txt";
    const string COUNTS_FILE = "word_counts.txt";
    const string CROSSREF_FILE = "cross_reference.txt";
    const string URLS_FILE = "urls.txt";

    ifstream fin(INPUT_FILE);
    if (!fin.is_open()) {
        cerr << "Nepavyko atidaryti failo " << INPUT_FILE << " skaitymui.\n";
        return 1;
    }

    // map<žodis, kiekKartu> žodžių skaičiavimui
    map<string, int> wordCount;
    // map<žodis, set<eilutėsNumeris>> eilutės, kuriose pasikartojo žodis
    map<string, set<int>> crossRef;

    // regex URL’ams: ieškos "http://...", "https://..." arba "www...."
    // [^\s]* paims viską iki pirmo tarpo
    regex urlRegex(R"((https?://[^\s]+)|(www\.[^\s]+))", regex::icase);

    vector<string> foundURLs;

    string line;
    int lineNumber = 0;
    while (getline(fin, line)) {
        lineNumber++;
        // 1) Ieškome URL’ų toje eilutėje
        {
            auto begin = sregex_iterator(line.begin(), line.end(), urlRegex);
            auto endIt = sregex_iterator();
            for (auto it = begin; it != endIt; ++it) {
                string url = it->str();
                foundURLs.push_back(url);
            }
        }

        // 2) Skaičiuojame žodžius eilučių ir kaupiame cross‐reference
        // Pirmiausia "išardome" eilutę į "žodžių gabalus" su istringstream
        istringstream iss(line);
        string rawWord;
        while (iss >> rawWord) {
            // nukerpame skyrybos ženklus gale ir pradžioje
            string cleaned = cleanWord(rawWord);
            if (cleaned.empty()) continue;
            // pavertėm mažosiomis, kad "Testas" ir "testas" būtų vienas žodis
            string low = toLowerStr(cleaned);

            wordCount[low]++;
            crossRef[low].insert(lineNumber);
        }
    }
    fin.close();

    // 3) Išvedame tik tuos žodžius, kurie pasikartojo daugiau nei 1 kartą
    ofstream foutCounts(COUNTS_FILE);
    if (!foutCounts.is_open()) {
        cerr << "Nepavyko sukurti " << COUNTS_FILE << " failo.\n";
        return 1;
    }
    foutCounts << "Žodžiai, pasikartoję daugiau nei 1 kartą:\n";
    for (auto& p : wordCount) {
        if (p.second > 1) {
            foutCounts << p.first << " -> " << p.second << "\n";
        }
    }
    foutCounts.close();

    // 4) Išvedame cross-reference lentelę (tik žodžiai, kurie pasikartojo >1 karto)
    ofstream foutCross(CROSSREF_FILE);
    if (!foutCross.is_open()) {
        cerr << "Nepavyko sukurti " << CROSSREF_FILE << " failo.\n";
        return 1;
    }
    foutCross << "Cross-reference (žodžiai, pasikartoję >1 kartą, ir jų eilučių numeriai):\n";
    for (auto& p : crossRef) {
        const string& word = p.first;
        const set<int>& lines = p.second;
        if (wordCount[word] > 1) {
            foutCross << word << " -> eilutės: ";
            bool pirmas = true;
            for (int ln : lines) {
                if (!pirmas) foutCross << ", ";
                foutCross << ln;
                pirmas = false;
            }
            foutCross << "\n";
        }
    }
    foutCross.close();

    // 5) Išvedame rastus URL’us į atskirą failą
    ofstream foutURLs(URLS_FILE);
    if (!foutURLs.is_open()) {
        cerr << "Nepavyko sukurti " << URLS_FILE << " failo.\n";
        return 1;
    }
    foutURLs << "Rasti URL'ai:\n";
    for (auto& u : foundURLs) {
        foutURLs << u << "\n";
    }
    foutURLs.close();

    cout << "Viskas baigta! Rezultatai į:\n"
         << "- " << COUNTS_FILE << "\n"
         << "- " << CROSSREF_FILE << "\n"
         << "- " << URLS_FILE << "\n";

    return 0;
}

