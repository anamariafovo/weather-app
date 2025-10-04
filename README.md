### How to run:

1. Switch to the ./src folder: `cd src`
2. Compile all .cpp files: `g++ *.cpp -o weatherApp`
3. Run the program: `./weatherApp`

### Functionalities:

1. **Compute temperature data:** displays a table of temperature data (open, highest, lowest, close).
2. **Plot candlestick:** plots the same data.
3. **Filter by date range:** filters by date rango for the chosen time period (yearly, monthly, daily); can also choose between plot or raw data.
4. **Filter by temperature range:** filters by temperature range (minimum & maximum); can also choose between plot or raw data.
5. **Predict temperature for a future year:** choose a start and end year for training the model, then choose the year to predict the average temperature for.
6. **Help:** displays help instructions,
7. **Exit:** exits the program,

### How to use each feature for fetching temperature data:

Note: all temperature data can be computed yearly, monthly or daily for the chosen country (ex. RO_temperature, AT_temperature, GB_temperature, etc.)

-   first, choose one option from the menu (1 - 4)
-   choose yearly, monthly or daily option (1 - 3)
-   choose the country (ex. GB_temperature)
-   choose the time (ex. 2002 for year, 03 for month, 08 for day)
