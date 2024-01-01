Tento projekt simuluje průběh epidemie pomocí modelu SIR. Nejprve přijme data a poté vrátí soubor html.
Kliknutím na soubor html uvidíte dva grafy. První graf zobrazí data ze souboru csv a druhý graf modeloval data.

Pro sestavení kódu použijte cmake. Buďte opatrní, protože CMakeLists.txt vyžaduje verzi alespoň 3.20

Při kompilaci programu jej budete moci spustit, níže je uveden příklad spuštění programu.

./Epidemiological_modeling --real-data <název souboru csv>.csv --infectious_days 8 --infections_per_day 0.3 --output index.html

Pro parametr --real-data použijte soubor csv
Pro parametr --infectious_days použijte celé číslo
Pro parametr --infections_per_day použijte číslo float
Pro parametr --output můžete napsat libovolný název, ale musí být ve formátu .html
