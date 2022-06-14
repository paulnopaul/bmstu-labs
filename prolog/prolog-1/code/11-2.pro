domains
	name, university, phone_number = symbol
	id = integer
predicates
student(id, name).
phone (id, phone_number).
study (id, university).
in_university(name, university).
has_phone(name, phone_number).
clauses
student(1, "Alexey Petrov").
student(2, "Mihkail Kotikov").
student(3, "Alexandra Spiridonova").

phone(1, "123123").
phone(2, "312321").
phone(3, "19191919").

study (3, msu).
study (1, bmstu).
study (2, bmstu).

in_university(Name, University) :- student(Id, Name), study(Id, University).
has_phone(Name, Phone) :- student(Id, Name), phone(Id, Phone).

goal

% in_university(X, bmstu).
% has_phone(X, "312321").
in_university("Alexey Petrov", University).


