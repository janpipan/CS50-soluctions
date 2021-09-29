-- Keep a log of any SQL queries you execute as you solve the mystery.

-- searching for description of what happend to get more information
SELECT description FROM crime_scene_reports
    WHERE year = 2020 AND day = 28 AND month = 7 AND street = "Chamberlin Street";
-- 10:15 am Chamberlin street courthouse

-- searching for interviews that included courthouse
SELECT name, transcript FROM interviews
    WHERE year = 2020 AND day = 28 AND month = 7 AND transcript LIKE "%courthouse%";
-- thief got into car and drove away within ten minutes of theft
-- thief withdrew money on ATM on Fifer Street
-- talking on phone with someone about taking the earliest flight of Fiftyville the next day, and asked his accomplice to purchase tickets for flight, phone call duration was shorter than a minute

-- searching for license plates that left the corthouse within ten minutes of theft
SELECT activity, license_plate FROM courthouse_security_logs
    WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25;

-- searching for transactions of ATM on Fifer Street
SELECT transaction_type, amount, account_number FROM atm_transactions
    WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street";

-- searching for passengers on flights the next day
SELECT passengers.passport_number, hour FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE flights.year = 2020 AND flights.day = 29 AND month = 7 AND airports.city = "Fiftyville";

SELECT caller, receiver FROM phone_calls
     WHERE year = 2020 AND day = 28 AND month = 7;

-- searching for thief
SELECT name, passport_number FROM people
    WHERE phone_number IN (SELECT caller FROM phone_calls
                                WHERE year = 2020 AND day = 28 AND month = 7)
        AND passport_number IN (SELECT passengers.passport_number FROM passengers
                                    JOIN flights ON passengers.flight_id = flights.id
                                    JOIN airports ON airports.id = flights.origin_airport_id
                                    WHERE flights.year = 2020 AND flights.day = 29 AND flights.month = 7 AND airports.city = "Fiftyville" AND flights.hour = 8)
        AND license_plate IN (SELECT license_plate FROM courthouse_security_logs
                                WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25)
        AND id IN (SELECT person_id FROM bank_accounts
                        WHERE account_number IN (SELECT account_number FROM atm_transactions
                                                     WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
--Thief is Ernest

-- searching for esacping place
SELECT city FROM airports
    WHERE id = (SELECT destination_airport_id FROM flights
                    JOIN airports ON airports.id = flights.origin_airport_id
                    WHERE flights.year = 2020 AND flights.day = 29 AND flights.month = 7 AND flights.hour = 8 AND flights.origin_airport_id IN (SELECT airports.id FROM airports WHERE city = "Fiftyville"));
-- London

-- searching for accomplice
SELECT name FROM people
    WHERE phone_number IN (SELECT receiver FROM phone_calls
                                WHERE caller IN (SELECT phone_number FROM people
                                                            WHERE name = "Ernest" AND passport_number = "5773159633")
                                AND year = 2020 AND day = 28 AND month = 7 AND duration < 60);


