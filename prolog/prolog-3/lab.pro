domains
name, phone, city, street, model, color, bank, account = symbol
house, room, price, money = integer
address=addr(city, street, house, room).
property=car(model, color, price);building(price);area(price);water_transport(price).
predicates
phone(name, phone, address).
bank_account(name, bank, account, money).
has_property(name, property).
property_price(name, property, price).
property_prices(name, price).
sum_all_prices(name, price).
clauses
phone(ivanov, "89055477656", addr(moscow, pushkinskaya, 10, 10)).
phone(tsvetkov, "83399939393", addr(moscow, pushkinskaya, 11, 10)).
phone(kotegov, "12091230912", addr(moscow, baumanskaya, 33, 22)).


bank_account(ivanov, tinkoff, a012331, 10).
bank_account(ivanov, alfabank, x130129jf, 100).
bank_account(tsvetkov, alfabank, jfjfjfjfj, 300).
bank_account(kotegov, sberbank, oijsdfoij, 400).
bank_account(kotegov, raiffeisen, nsdfff, 500).

has_property(tsvetkov, car(zhiguli, red, 2)).
has_property(tsvetkov, building(2)).
has_property(tsvetkov, area(3)).
has_property(tsvetkov, water_transport(4)).

has_property(kotegov, car(zhiguli, red, 3)).
has_property(kotegov, building(2)).
has_property(kotegov, area(3)).
has_property(kotegov, water_transport(4)).

has_property(ivanov, car(zhiguli, red, 1)).
has_property(ivanov, building(2)).
has_property(ivanov, area(3)).
has_property(ivanov, water_transport(4)).


property_price(Name, building(Price), Price) :- has_property(Name, building(Price)).
property_price(Name, car(_, _, Price), Price) :- has_property(Name, car(_, _, Price)).
property_price(Name, area(Price), Price) :- has_property(Name, area(Price)).
property_price(Name, water_transport(Price), Price) :- has_property(Name, water_transport(Price)).

property_prices(Name, Price) :- property_price(Name, _, Price).

sum_all_prices(Name, Sum) :- property_price(Name, building(BuildingPrice), BuildingPrice),
property_price(Name, car(_, _, CarPrice), CarPrice),
property_price(Name, area(AreaPrice), AreaPrice),
property_price(Name, water_transport(WaterPrice), WaterPrice),
Sum = BuildingPrice + CarPrice + AreaPrice + WaterPrice.


goal
% has_property(ivanov, X).
% property_price(ivanov, Name, X).
sum_all_prices(ivanov, Sum).

