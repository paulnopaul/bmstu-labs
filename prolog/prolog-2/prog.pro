domains
name, phone, city, street, model, color, bank, account = symbol
house, room, price, money = integer
address=addr(city, street, house, room).
predicates
phone(name, phone, address).
car(name, model, color, price).
bank_account(name, bank, account, money).
car_by_phone(phone, name, model, color, price).
info_by_name_and_city(name, city, street, bank, phone).
clauses
phone(ivanov, "89055477656", addr(moscow, pushkinskaya, 10, 10)).
phone(tsvetkov, "83399939393", addr(moscow, pushkinskaya, 11, 10)).
phone(kotegov, "12091230912", addr(moscow, baumanskaya, 33, 22)).

car(tvetkov, bugatti, black, 100000000).
car(ivanov, zhiguli, red, 123123).
car(ivanov, ferrari, orange, 3333333).

bank_account(ivanov, tinkoff, a012331, 10).
bank_account(ivanov, alfabank, x130129jf, 100).
bank_account(tsvetkov, alfabank, jfjfjfjfj, 300).
bank_account(kotegov, sberbank, oijsdfoij, 400).
bank_account(kotegov, raiffeisen, nsdfff, 500).

car_by_phone(Phone, Name, Model, Color, Price) :- phone(Name, Phone, _), car(Name, Model, Color, Price).

info_by_name_and_city(Name, City, Street, Bank, Phone) :- phone(Name, Phone, addr(City, Street, _, _)), bank_account(Name, Bank, _, _).


goal
% car_by_phone("89055477656", N, M, C, P).
% car_by_phone("89055477656", _, M, _, _).
info_by_name_and_city(kotegov, moscow, S, B, P).

