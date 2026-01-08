from pyperclip import copy

def getFileLines(file_name: str) -> list[str]:
	file_content = ""

	try:
		with open(file_name, "r") as f:
			try:
				file_content = f.read()
			except UnicodeDecodeError as err_msg:
				file_content = ""

				print(f"Undefined character: {err_msg}")

	except FileNotFoundError:
		print(f"Error: File {file_name} not found.")

		return []

	return file_content.splitlines()

if __name__ == "__main__":
	#file_name = input("Enter file name: ")
	
	#file_lines = getFileLines(file_name)

	file_name = "H:\\Downloads\\Вайбовые песни ( по мнению автора ).txt"

	file_lines = """Элджей - V ecstase
Макс Корж - Слово пацана
Кэнни · МС Дымка - Ворона
VERKA SERDUCHKA - Всё будет хорошо
Dunderpatrullen - We Are Number One (Remix)
Idris & Leos, NILETTO - Дурная привычка (Премьера клипа)
NЮ — «Я так тебя люблю»
NЮ - Если сгорим
NЮ - Некуда бежать
Танцы Минус - Половинка
Кино - Закрой за мной дверь
Ногу Свело! - Наши юные смешные голоса
Полиграф ШарикOFF - Харизма
Дайте танк (!) - Люди
Екатерина Яшникова - Я останусь одна
Группа Секрет - Моя любовь на пятом этаже
Жуки - Йогурты
NЮ feat. Николай Монро - Я буду бухать
SLAVA MARLOW, Элджей — БОЛЬШИЕ ДИСКИ (◎-◎；) [ЭЛЬФ 1]
NLO - Не грусти (Премьера клипа 2021)
Lizer  - Пачка Сигарет (prod. by boyfifty)
MORGENSHTERN - Ретро Рейв (Премьера Клипа 2021)
TROJAC (REMIX) [KRV NIJE VODA]
MORGENSHTERN - Селяви
Нурминский - Валим (официальный клип)
MORGENSHTERN - GTA (Премьера клипа, 2021)
Rakhim - Синий Lamborghini (Official Music Video)
Ицык Цыпер и Игорь Цыба  - Дымок
SLAVA MARLOW X FREE FIRE - МИЛЛИОН ДОРОГ (ПРЕМЬЕРА КЛИПА!!!)
Элджей, Onative - MAC&CHEESE
NLO - НАПИВАЮСЬ
SLAVA MARLOW - Ты Далеко
MORGENSHTERN x TIMURKA BITS - КОПЫ НА ХВОСТЕ [Премьера Клипа, 2019]
Konfuz — Ратата (Mood video)
SLAVA MARLOW, Градусы — СУМАСШЕДШИЕ_♡_´∀｀_人_´∀｀_♡_ [ЭЛЬФ 1]
MORGENSHTERN - ICE (feat. MORGENSHTERN)
10AGE — Нету интереса | ПРЕМЬЕРА КЛИПА!
SLAVA MARLOW, SALUKI — НЕ ЗАБЫЛ ╥﹏╥  [ЭЛЬФ 1]
BITTUEV - Братик (официальный клип 2021)
SLAVA MARLOW - По Глазам
SLAVA MARLOW, ЛСП — Я НЕНАВИЖУ ЭТОТ ТРЕК!!! 凸￣ヘ￣ [ЭЛЬФ 1]
MORGENSHTERN, Onative, Rich The Kid - IF I EVER (Official Video, 2023)
MORGENSHTERN - UGU (Lyrics + Eng Subs)
MORGENSHTERN - Вот Так (Финал Трилогии, 2018)
Miyagi & Andy Panda - Minor (Mood Video)
Sam Wick - Сон (Official clip)
MACAN - Кино (Официальная премьера трека)
VERKA SERDUCHKA - Novogodnyaya
ШАРЛОТ & MORGENSHTERN - Малышка (Love Video 2020)
SQWOZ BAB – GENDER (Official video)
MORGENSHTERN - Новый Мерин (купил машину и снял клип, 2019)
MORGENSHTERN, SODA LUV, blago white, MAYOT & OG Buda - Cristal & МОЁТ (Remix) [Official Video, 2021]
BULA & SVNV - Тлеет (Официальный клип)
MORGENSHTERN - ПОЙДЕТ (Веселый Клип, 2023)
XXXTENTACION - MOONLIGHT (OFFICIAL MUSIC VIDEO)
MORGENSHTERN - YUNG HEFNER (Клипец, 2020)
NLO - Мир холодный (Премьера клипа 2021)
ТАЙПАН & Agunda - Луна не знает пути (Премьера клипа)
MORGENSHTERN & Тимати - El Problema (Prod. SLAVA MARLOW) [Премьера Клипа, 2020]
kostromin — Моя голова винтом (My head is spinning like a screw) (Official Video)
SLAVA MARLOW & MK - Нет Проблем
Rauf & Faik — детство (Official video)
Tanir & Tyomcha - Потеряли пацана (Lyric Video)
SLAVA MARLOW - КАМРИ 3.5
MORGENSHTERN & Элджей - Cadillac (СЛИВ КЛИПА, 2020)
Пика - Патимейкер (Ploty prod)
Джаро & Ханза - Королева танцпола (Официальное видео 2019)
Джарахов & Markul – Я в моменте (Mood video by Alina Pasok)
SLAVA MARLOW - Хотел тебе сказать…
QP Show - Непохожие (Премьера клипа, 2016)
MORGENSHTERN - 12 (Official Video, 2022)
Кот - Почему молчат твои глаза (ПРЕМЬЕРА ТРЕКА)
Тима Белорусских - Аленка (песня)
SLAVA MARLOW & ЭЛДЖЕЙ - ЗЛОЙ
Danya Milohin · Mumiy Troll - Bashnia
Filatov & Karas · Mumiy Troll - Amore More, Goodbye
Алла Пугачёва - Позови меня с собой (Official HD Video)
ГУДЗОН - Влюбилась в пацана
Канги - Времена
Netsignala - На своей волне
HOLLYFLAME · Лапай Владислав Александрович - Рваные мысли
Arthur Pirozhkov · Klava Koka - Khochesh
просто Лера · Розниченко Александр Русланович - Лютики
GSPD - РОБОТ
GSPD - Первое свидание
GSPD - ЗАБЕРИ МОЮ МОЛОДОСТЬ
Алексей Чумаков - Арабская ночь (2019)
Бабек Мамедрзаев - Принцесса (Премьера клипа, 2020)
Ваня Дмитриенко - Венера-Юпитер
Тима Белорусских - Окей (трек)
ПНЕВМОСЛОН - Принцесса В Трусах С Алиэкспресса
winver · winver · Jude Wolf - это путин виноват mylancore
Toby Fox - Spider Dance
The Beatles - Let It Be (Remastered 2015)
Chess Type Beat | joyful - chess (slowed)
GSPD - герменевтика
maxxytren · bulk_machine - ГИМН КАЧКОВ
NLO · Рудницкий Степан Александрович · Шамов Евгений Александрович - Чё хочу
VESNA305 - Новый год
Imagine Dragons - Follow You
Тима Белорусских · Морозов Тимофей Андреевич - Окей
Arnon · letskillua - Te Molla
Quest Pistols - Ты так красива
Carla's Dreams - Sub Pielea Mea | #Eroina
Carla's Dreams - Sub pielea mea (Midi Culture Remix)
Океан Ельзи - Обійми
Тима Белорусских - Мокрые кроссы
The Strumbellas - Spirits
Zivert - Зелёные волны
Ваня Дмитриенко - Шёлк
ESTRADARADA - Вите Надо Выйти
NЮ - Дураки
Ласковый Май - Розовый вечер
SeO - Я это ты
NЮ - Веснушки
NILETTO - Ты такая красивая
NЮ - Грустно Вале
Imagine Dragons - Demons
Jovani · Chris Crone - I'll Fly With You (L'Amour Toujours)
Tom Odell - Another Love
Imagine Dragons - Bad Liar
Minelli - Rampampam | Official Video
Канги, Galust — Голова | ПРЕМЬЕРА КЛИПА
Гречка – Люби меня люби
МС Вспышкин и Никифоровна-Меня Прёт, Новогодняя
Intelligency - August | Russian Version
Ленинград — i_$uss
NBSPLV - The Lost Soul Down
Грибы - Бери грибы
Billie Eilish - bad guy
HOLLYFLAME - Половина меня
АИГЕЛ - Пыяла
Palina - Позови меня с собой
MATRANG - Заманчивая
Тима Белорусских - Руферы
Alis Shuka - Not About Us (Byjoelmichael Remix)
Lykke Li - I Follow Rivers
NEMIGA - Лепестки (EGOPIUM Remix)
Adam Lambert - Ghost Town
Артем Пора Домой · MVGMA · Маша и Медведи · Смирнов Александр Сергеевич · Алымов Артем Алексеевич · Макарова Мария Владимировна - ЗЕМЛЯ
plenka - Closed
ANIKV - там, где хорошо
Else - Paris
FILV, Edmofo feat. Emma Peters - Clandestina
Palina - Месяц
Mahmut Orhan · Sena Sener - Feel (Radio Edit)
The Neighbourhood - Sweater Weather (Gaullin Remix) / (Legendado)
Тима Белорусских - Отпусти
ZYZZCVNT · Alexander Tretyakov - INSONAMIA
Miyagi & Andy Panda - Yamakasi
XOLIDAYBOY - Мания (Mood Video)
Клава Кока & Руки Вверх - Нокаут (Премьера клипа, 2021)
Леша Свик - Малиновый Свет | Official Video
NILETTO - Ветер зимаря (Официальный Танец Шафл)
6.Тима Белорусских - Мальчик - бабл - гам
NЮ - Веснушки (Клип 2019)
1.Тима Белорусских - Я больше не напишу
RAKHIM - СИНИЙ LAMBORGHINI (ПРЕМЬЕРА КЛИПА, 2021)
Премьера! Тима Белорусских - Мокрые кроссы + Незабудка. Два клипа - одна история
BØRNS | "Past Lives" (Audio) | Interscope
HOLLYFLAME · Владислав Александрович Лапай - Красками
Zedd · Jon Bellion - Beautiful Now
Alan Walker · David Whistle - Routine
Земфира - П.М.М.Л.
Земфира - ИСКАЛА
Shanguy - King of the Jungle
The Black Eyed Peas - The Time (Dirty Bit)
David Rush · Pitbull · Kevin Rudolf · LMFAO - Shooting Star (Party Rock Mix)
The Black Eyed Peas - Meet Me Halfway
will.i.am · Britney Spears - Scream & Shout
Jennifer Lopez · Pitbull - On The Floor (Radio Edit)
Deorro · Chris Brown - Five More Hours
Teriyaki Boyz - Tokyo Drift (Fast & Furious)
Nakama - DIA DELÍCIA
LMFAO · Lauren Bennett · GoonRock - Party Rock Anthem
【和訳】Oliver Tree「Life Goes On」【公式】
Sub Urban - Cradles | Pop | NCS - Copyright Free Music
Imagine Dragons - Bad Liar
Trevor Daniel - Falling (Official Music Video)
Сателлит · Антонов Виктор Викторович - Преданная
NЮ - Больше не полетаем
Dabro - Ты люби так же
Мария Зайцева - Призрак
Amirchik - Эта любовь
Tanin Jazz · Tania Haroshka - Виртуальная любовь
The Irrepressibles - In This Shirt
Tom Odell - Another Love (Official Video)
Billie Eilish - bad guy
NEFFEX - Fight Back
Artemas - i like the way you kiss me (lyric video)
Post Malone - rockstar (Official Music Video) ft. 21 Savage
Bella Poarch - Build a B*tch (Official Music Video)
Powfu - death bed (coffee for your head) (Official Video) ft. beabadoobee
SKRILLEX - Bangarang feat. Sirah [Official Music Video]
Lost Sky - Fearless Pt II (Feat. Chris Linton) [Official Lyric Video]
Oliver Tree - Life Goes On [Lyric Video]
Sub Urban - Cradles [Official Music Video]
MC Zali - Люба Ивана
ABBA - Gimme! Gimme! Gimme! (A Man After Midnight)
Icona Pop - Emergency
Alan Walker · Steve Aoki · ISÁK · Omar Noir - Lonely
Jax Jones · MNEK - Where Did You Go?
NLO · Leonid Rudenko · REFLEX · Войналович Елена Анатольевна · Кулыгин Глеб Сергеевич · Рудницкий Степан Александрович · Шамов Евгений Александрович · Тюрин Вячеслав Владимирович · Белявцев Евгений Александрович · Руденко Леонид Анатольевич - Танцы 2.0
NLO · Рудницкий Степан Александрович · Шамов Евгений Александрович - Не грусти
MORGENSHTERN · Vitja AK - RATATATATA
Тима Белорусских - Я больше не напишу
Y2K · bbno$ - Lalala
Shawn Mendes · Camila Cabello - Señorita
Rixton - Me And My Broken Heart
The Black Eyed Peas - Pump It
Portugal. The Man - Feel It Still
ALMARY - До скорых встреч
RASA - ФИОЛЕТОВО ( ПРЕМЬЕРА КЛИПА 2019 )
Lely45 - Восемь
Дима Билан - Невозможное возможно
Little Big - I`m OK
Ленинград - i_$uss
Руки Вверх - 18 Мне уже
CREAM SODA · KHLEB - Plachu na tekhno
plenka - Call Me (Slowed)
plenka - Nightmare
MOUNT · Noize Generation - Around The World
Gaullin · Julian Perretta - Seven Nation Army
Aaron Smith - Dancin (KRONO Remix) - Lyrics
AronChupa · Little Sis Nora - I'm an Albatraoz
Tiësto - The Business
Gotye · Kimbra - Somebody That I Used To Know
ATB · Topic · A7S - Your Love (9PM)
Нина Бродская   -     Теряют люди друг друга   или  С любовью встретиться проблема трудная
SOVIET MARCH - Red Alert 3 - RUSSIAN COVER (Composer James Hannigan)
Владимир Высоцкий - Утренняя гимнастика
Vitas - The 7th Element / Седьмой элемент (Настоящий новый год 2.0)
«Катюша»
Trololo Sing Along!
Эдуард Хиль - Trololo / Я очень рад, ведь я наконец возвращаюсь домой
Modern Talking - Brother Louie
CYGO - Panda E
MATRANG - Медуза
Little Big · Илья Прусикин · Любим Хомчук - Faradenza
The Black Eyed Peas - Let's Get It Started (Spike Mix)
twenty one pilots - Heathens
Imagine Dragons x J.I.D - Enemy (from the series Arcane League of Legends)
Ace of Base - All That She Wants
Ace of Base - All That She Wants (Official Music Video)
Mike Perry - The Ocean ft. Shy Martin
The Black Eyed Peas - Let's Get It Started
twenty one pilots: Heathens (from Suicide Squad: The Album) [OFFICIAL VIDEO]
LITTLE BIG – FARADENZA (official music video)
Шура - Слушай
R.Riccardo - Твои поцелуи
Мот - День и Ночь (премьера клипа, 2015)
MATRANG - Медуза
Егор Крид - Самая Самая (Премьера клипа, 2014)
Алексей Воробьёв - Сумасшедшая
IOWA - Простая Песня
Dabro - Ты знаешь, мам (Official video)
5sta Family & 2345 - Я Буду [HD]
XOLIDAYBOY - Моя Хулиганка (Official Video)
Егор Крид & MOLLY - Если ты меня не любишь (премьера клипа, 2017)
Liaze · NILETTO · Jaschka · equal · equal - Goluboi Wagon (Голубой вагон)
Fareoh - Cloud Ten | Trap | NCS - Copyright Free Music
BENNETT - Vois sur ton chemin - DJ Holanda MONTAGEM CORAL Remix (Official Audio Video)
LONOWN - AVANGARD (SLOWED) [Official Visualizer]
ريكمس حماسي 🔥- Blue (Video Music official)
deprezz - Vois Sur Ton Chemin
Alan Walker - Sing Me To Sleep
TheFatRat - Time Lapse
Fareoh - Under Water | Trap | NCS - Copyright Free Music
Eurythmics, Annie Lennox, Dave Stewart - Sweet Dreams (Are Made Of This) (Official Video)
ЛюSEA · DV Street - Дороже золота
Calvin Harris - My Way (Official Video)
Ava Max - My Head & My Heart [Official Music Video]
MARUV & BOOSIN — Drunk Groove (Official Video)
Lost Frequencies - Are You With Me (Official Music Video)
Axwell /\\ Ingrosso, Axwell, Sebastian Ingrosso - More Than You Know
Dj Kantik - Teriyaki Boyz - Tokyo Drift & Sean Paul - Temperature (Remix)
ATB, Topic, A7S - Your Love (9PM) (Official Music Video)
Clean Bandit - Solo (feat. Demi Lovato) [Official Video]
Robin Schulz - Sugar (feat. Francesco Yates) (OFFICIAL MUSIC VIDEO)
ZHU - Faded (Official Music Video)
Imany - Don't Be So Shy (Filatov & Karas Remix) / Official Music Video
Tiësto & Ava Max - The Motto (Official Music Video)
Alan Walker & ISÁK - Sorry (Official Music Video)
Avicii - Levels
LITTLE BIG — I'M OK (official music video)
Lost Frequencies ft. Calum Scott - Where Are You Now (Official video)
Tiësto - The Business (Official Music Video)
Артур Пирожков - туДЫМ-сюДЫМ  [Премьера клипа 2020]
Ленинград — Ч.П.Х.
Егор Крид - Невеста (Премьера клипа, 2015)
Те100стерон - Это не женщина
Алексей Воробьев - Самая красивая (Сумасшедшая 2)
NYUSHA / НЮША - Выбирать чудо (Full HD)
RASA - Пчеловод  | ПРЕМЬЕРА КЛИПА 2019
Иванушки Int. - Тополиный пух
Дима Билан - Невозможное возможно
Сергей Лазарев - Это все она (Official video)
LITTLE BIG - LollyBomb [Official Music Video]
GAYAZOV$ BROTHER$ — МАЛИНОВАЯ ЛАДА (ПРЕМЬЕРА КЛИПА 2021)
Cream Soda & Хлеб - Плачу на техно (премьера клипа)
Bearwolf - Валькирия
БиС - Катя
Коста Лакоста, Ольга Серябкина — По улицам (Official Music Video)
MORGENSHTERN - ПОВОД (Lyric Video, 2025)
Vitas - Opera #2
Алексей Воробьев - Я тебя люблю
Dabro - Услышит весь район (Official video)
Потап и Настя - Умамы
Макс Корж — Жить в кайф (official video)
IOWA - Улыбайся
Артур Пирожков - Зацепила (Премьера клипа 2019)
Звери - До скорой встречи
RASA - ПОГУДИМ (ПРЕМЬЕРА КЛИПА)
GAYAZOV$ BROTHER$ & Filatov & Karas — ПОШЛА ЖАРА (премьера клипа 2021)
Натали - О Боже, какой мужчина! [Official Video]
Филипп Киркоров - Цвет настроения синий
Винтаж · Зараза - Eva 2.0
Пропаганда - Мелом (Official Video) 2001 12+
Султан-Ураган и Мурат Тхагалегов На дискотеку [Official Music Video] HD
Ласковый Май ( солист Юра Шатунов ) - Седая ночь (Версия 2019 год).
Руки Вверх! - Крошка моя
Руслан Набиев feat  A-Sen По Ресторанам (Dj Fat Maxx Remix)
Григорий Лепс - Рюмка водки на столе (official Video 2003)
Arthur Pirozhkov - #Alkogolichka
Коста Лакоста · SERYABKINA - По улицам
BEARWOLF · Василевская Валерия Алексеевна · Рычагов Георгий Михайлович - Валькирия
Винтаж - Ева
MARUV - Siren Song
Олег Кензов - По Кайфу
LIRANOV - Гюрза
AP$ENT · harddope · PHURS - Можно я с тобой (Remix)
Arthur Pirozhkov - Ona reshila sdat'sja
Люся Чеботина - СОЛНЦЕ МОНАКО
Джиган · Юлия Савичева - Отпусти (feat. Юлия Савичева)
ALMARY - До скорых встреч (Премьера клипа 2024)
Timran, Zell, Batrai feat. Aslai - Не пускайте танцевать
ANIVAR - Украду
я про рок · Воротникова Елизавета Николаевна · Арустамов Роман Романович - ангел-хранитель
Дискотека Авария · Николай Басков - Фантазёр
Galibri & Mavik · DJ DimixeR - Взгляни на небо (Remix)
Слава - Одиночество-сука
Егор Крид - Невеста
Татьяна Куртукова - Матушка
Казачки Кавказа - Русская рать
MORGENSHTERN - ЧЕРНЫЙ РУССКИЙ (Клип, 2023)
Ойся ты ойся   Если Девушка Казачка   Kazachka
Олег Газманов - Вперед, Россия! 4K видео
Dzharakhov · Markul - Ya v momente
SEVILLE - Гори, гори (OST "Дайте шоу")
Юлия Савичева - От его голоса
Galibri & Mavik - Федерико Феллини
XOLIDAYBOY - Океаны
LXNGVX · Warriyo - Mortals Funk Remix
Calvin Harris - Summer
Steve Aoki · Alan Walker · ISÁK - Are You Lonely
Роки · Мисан Кирилл Сергеевич · Едигаров Никита Михайлович - Лабиринт
Баста - Выпускной (Медлячок)
Группа "Градусы" - Заметает
Мари Краймбрери - Мне так повезло
Akmal' - Iz-za tebya
тима ищет свет · Якимов Тимофей Алексеевич - волна
Ани Лорак · Кузнецова Дарья Сергеевна · Гуцериев Михаил Сафарбекович - Рядом, но не вместе
VESNA305 - Глупая девочка
GAYAZOV$ BROTHER$ - MALINOVAYA LADA
Юлия Савичева - Привет
Те100стерон - Это не девочка
CG5 - I See A Dreamer
RADWIMPS - すずめ feat.十明 [Official Lyric Video]
TheFatRat - The Calling (feat. Laura Brehm)
Alan Walker · Noah Cyrus · Digital Farm Animals · Juliander - All Falls Down
SAINt JHN - Roses (Imanbek Remix)
NILETTO - Счастливым
Alok · Zeeba · IRO - Ocean
Lilly Wood & The Prick - Prayer In C (Live @ Main Square 2015)
Wiz Khalifa - See You Again ft. Charlie Puth [Official Video] Furious 7 Soundtrack
@RihannaVEVO  - Diamonds (Jerber lazaro Remix)
Imagine Dragons - Demons (Official Music Video)
Vicetone - Nevada (feat. Cozi Zuehlsdorff) [Monstercat Official Music Video]
Kungs vs Cookin’ on 3 Burners - This Girl
The Chainsmokers ft. Daya - Don't let me down(edgyAR remix)
Cat Dealers, Bruno Martini, Joy Corporation - Gone Too Long (Official Music Video)
Tinlicker & Helsloot - Because You Move Me (Official Music Video)
Kastuvas - Keep on Moving (feat. Emie)
Alok - Love Again (feat. Alida) [Official Music Video]
Jovani x Chris Crone - I'll Fly With You (L'Amour Toujours) [Official Video]
Zerrin Temiz & Serhat Durmus | Hislerim
Lost Frequencies feat. Janieck Devy - Reality (Official Music Video)
Aaron Smith - Dancin - Krono Remix (Official Video) ft. Luvli
Alan Walker - Diamond Heart (feat. Sophia Somajo)
Alan Walker, Sofiloud - Team Side feat. RCB (Official Music Video)
Petit Biscuit - Sunset Lover (Official Music Video)
Ofenbach - Overdrive feat. Norma Jean Martine (Official Music Video)
Alan Walker x Imanbek - Sweet Dreams (Official Music Video)
Avicii - Waiting For Love
twenty one pilots: Stressed Out [OFFICIAL VIDEO]
Pascal Letoublon - Friendships (Lost My Love) (Lyric Video) ft. Leony
DubDogz & Bhaskar - Infinity (DubDogz & Bhaskar Edit) [Official Music Video]
Alok, Bruno Martini feat. Zeeba - Hear Me Now (Official Music Video)
Дмитрий Колдун - Приду без повода
XOLIDAYBOY - Люмены
Quest Pistols Show - Непохожие
Егор Крид - Самая самая
Конец Фильма - Юность в сапогах
INTERWORLD - METAMORPHOSIS | Lyrics
Syko - Brooklyn Blood Pop (Instrumental / Monsieur Zy Remix) [NCS Fanmade]
Lunak - I Feel Alive ♪
Gozzy - YOUR EYES
Юлия Проскурякова - Ты мое счастье
Dua Lipa - Levitating Featuring DaBaby (Official Music Video)
Ava Max - Kings & Queens [Official Music Video]
Clean Bandit - Rockabye (feat. Sean Paul & Anne-Marie) [Official Video]
AronChupa, Little Sis Nora - I'm an Albatraoz | OFFICIAL VIDEO
Imagine Dragons - Bones (Official Audio)
GAYLE - abcdefu (Official Music Video)
РОЖЕВЕ ВИНО (ПАРОДІЯ)
MORGENSHTERN · Eldzhey - Cadillac
SLAVA MARLOW - MILLION DOROG
Время и Стекло - Навернопотомучто (Audio)
Руки Вверх - 18 Мне уже
Время и Стекло   Имя 505 (имя любимое моё)
Philip Koutev Ensemble - Бре, Петрунко
Eric Saade · Filatov & Karas · Gustaf Norén - Wide Awake (Red Mix)
Супер Жорик - Золото
VESNA305 - Новая новогодняя
5sta Family - Моя мелодия (DJ Pankratov)
ANIVAR - Лето
Zivert - Credo
Zvonkiy - Голоса
Ночные Снайперы - секунду назад
Рок-опера Орфей - Будь что будет
Смысловые Галлюцинации - Вечно молодой
Город 312 - Останусь (Radio Edit)
Женя Трофимов · Комната культуры · Трофимов Евгений Игоревич - Поезда
Антон Токарев - Седьмой лепесток
Любэ - Ты неси меня река (Краса)
Сергей Лазарев - Снег в океане
Братья Грим - Кустурица
Nebezao, NЮ - Если бы не ты
Те100стерон · Андрей Валериевич Бирбичадзе · Валери Валериевич Бирбичадзе - Это не женщина
XOLIDAYBOY - Кино
VESNA305 - Танцует Серёжка
Звери - Говори
Братья Поздняковы - Алло
T1One · Inur - Почему так больно
DEAF KEV · Sendi Hoxha - Invincible Pt. II
Ленинград - Экспонат
АНДРЕЙ КУКЛИН · Тихонов Андрей Андреевич · Куклин Андрей Владимирович - ВОДОПАДАМИ
Slavik Pogosov - Монро
MORGENSHTERN · Моргенштерн Алишер Тагирович · Катиков Андрей Александрович · Садыков Артур Равилевич · Макеев Дмитрий Юрьевич · Шкилев Павел Викторович · Андросов Сергей Анатольевич - ПУСТОЙ ВОКЗАЛ
Слава - Попутчица
Город 312 - Вне зоны доступа
JONY - Kometa
Zveri · Роман Билык - Районы-кварталы
XOLIDAYBOY - Мания
Oliver Tree · Little Big · Tommy Cash - You're Not There
DVRST · Игорь Скляр · Atomic Heart - Komarovo (DVRST Phonk Remix)
TheFatRat · Anjulie - Love It When You Hurt Me
Caravan Palace - Lone Digger
Ed Sheeran - Bad Habits
Группа "Градусы" - Режиссёр
Tanir & Tyomcha - Потеряли пацана
MORGENSHTERN - NOMINALO
Пика - Патимэйкер
Quest Pistols Show - Санта Лючия
DONI · Натали - Ты такой (feat. Натали)
Супер Жорик - Хочу тибя любицца
Алексей Воробьев - #Сумасшедшая
Ленинград - Ч.П.Х.
Big Baby Tape - Turbo (Majestic)
Потап и Настя - Все пучком
Дима Билан - Молния
DAVA · SERYOGA - CHYORNYJ BUMER (feat. SERYOGA)
Ирина Кайратовна - Айдахар
Band'Eros - Pro krasivuju zhizn'
Тимати - Я еду на джипе
Егор Крид · Филипп Киркоров - Цвет настроения чёрный (feat. Филипп Киркоров)
Даня Милохин · Николай Басков - Дико тусим
5sta Family - Вместе мы
ST · Ленинград - Балалайка
Потап и Настя - Чумачечая весна
Little Big - Go Bananas
Natan · Тимати - Дерзкая
Тимати · Рекорд Оркестр - Баклажан
HammAli & Navai - Ptichka
Тима Белорусских - Витаминка
HENSY - Поболело и прошло
PIZZA - Улыбка (Премьера, 2020)
VAVAN - Россия (Премьера клипа, 2025)
SEREBRO - Между нами любовь
Rauf & Faik, NILETTO - Если тебе будет грустно (Премьера клипа)
QUEST PISTOLS — Ты так красива (Официальный клип)
Егор Шип - DIOR (Премьера клипа, 2020) 12+
Элджей & Feduk - Розовое вино
Группа Пицца - Романс
Back in Black
MORGENSHTERN · Андрей Катиков · Моргенштерн Алишер Тагирович - TEASER
A.C.T. - Sugar
Capital Cities - Safe and Sound
Мэвл - Попытка номер 5
Alan Walker · YUQI · JVKE · (G)I-DLE - Fire!
NILETTO - Любимка
My Heart Will Go On - Recorder By Candlelight by Matt Mulholland
[RUSSIAN LITERAL] Assassin's Creed Revelations
Здравствуй дурка в облаках  | Animation | Анимация | Дурка |
VUDOO - Салам всем дворам
Яна Крапива - тело
МОТ - Август - это ты
GAYAZOV$ BROTHER$ - Do vstrechi na tantspole
FOGEL - STERVA
NЮ - Дым
🍀🍃А ты спой мне за Life🍃🍀
NAVAI · MONA - Есенин
Merab Amzoevi · Город 312 · Чебанов Николай Владимирович · Хайруллина Диляра Фанилевна · Притула Дмитрий Васильевич · Притула Леонид Васильевич - А я
ANIVAR - Любимый человек
Ksenon, XBRO - С какой стати?
Шуфутинский Михаил - 3-е сентября
Lely45 - Моя душа
Nebezao · Nola - Love Story
Кино - Группа крови
Тима Белорусских - Незабудка
Lizer - Пачка сигарет
NЮ - Выручай меня
NЮ - Вороны
NЮ - Отпустил
The Black Eyed Peas - Rock That Body
NЮ - Дави на газ
NЮ, Асия - Останься
NЮ - Я тебя обидел
NЮ - Никто
NЮ - Не получается
Post Malone · Swae Lee - Sunflower (Spider-Man: Into the Spider-Verse)
Elektronomia - Energy
Lilly Wood & The Prick and Robin Schulz - Prayer In C (Robin Schulz Remix) (Official)
Avicii - Levels (Radio Edit)
Andrea Bocelli · The Muppets - Jingle Bells
Flo Rida - Whistle
Flo Rida · Kesha - Right Round
Eminem - Without Me
Eminem - Mockingbird
Ampyx - Rise
Amadeus - Legendary
Pascal Letoublon - Friendships
ViveeysVault · Celestix - Heart Afire
Lost Sky - Fearless
Tobu · Itro - Cloud 9
TheFatRat - Windfall
Alan Walker - Fade
Electro-Light - Symbolism
Канги — Эйя (Official Music Video)
Alan Walker - Force
Mike Perry · Shy Martin · Mikael Persson - The Ocean
Different Heaven - Nekozilla
Dirty Palm · Micah Martin - Oblivion
XXXTENTACION - Moonlight
Clean Bandit · Demi Lovato - Solo (feat. Demi Lovato)
Lost Sky - Fearless
MORGENSHTERN - Я УБИЛ МАРКА (оксимирон дисс)
NЮ - Никто (клип)
Mary Gu - Косички (official mood video)
Альбертович - Я Не Люблю Учиться (Клип, 2025)
Trevor Daniel - Falling
ERA - Ameno (Official Music Video)
Daft Punk · Pharrell Williams · Nile Rodgers - Get Lucky (Radio Edit - feat. Pharrell Williams and Nile Rodgers)
Boom - Каникулы
Boom - How Do You Do
Руки Вверх - Пропадаешь зря
t.A.T.u. - Нас не догонят
Mr. President - Coco Jamboo
Modern Talking - Cheri Cheri Lady (New Version)
Демо - Солнышко
DJ SMASH - Волна (Remastered)
Alan Walker - Faded
TheFatRat · Shiah Maisel - Out Of The Rain
AJR - World's Smallest Violin
Lost Sky - Dreams
CHROMANCE · Marcus Layton - Wrap Me In Plastic (Marcus Layton Radio Edit)
The Chainsmokers · Daya - Don't Let Me Down
дипинс - Этажи
Бамбинтон - Зая
Alok · Zeeba · Bruno Martini - Hear Me Now
Babek Mamedrzaev - Printsessa
MARUV · Boosin - Drunk Groove
Axwell /\\ Ingrosso · Axwell · Sebastian Ingrosso - More Than You Know
DJ SMASH · MORGENSHTERN · Андрей Ширман · Алишер Моргенштерн - Новая волна
Rauf & Faik - eto li schast'e?
Edward Maya & Vika Jigulina - Stereo Love (Official Music Video)
ElyOtto - SugarCrash!
Sheet Music Boss - Rush E
Lalis Dream - Последний день лета
Руки Вверх! - 18 мне уже
Powerwolf - Nochnoi Dozor
SEREBRO - Мало тебя
Lida - Ради бога
Approaching Nirvana · Approaching Nirvana - Keystone
CMH · Lida - СТИКЕР
Mazario - Tetris (Techno Version)
Little Big - Koldunya
Король и Шут - Ведьма и Осёл
Король и Шут - Кукла колдуна
Король и Шут - Лесник
Bee Gees - Stayin' Alive (Official Music Video)
Yolanda Be Cool & DCUP - We No Speak Americano (Official Video)
Стас Костюшкин - Женщина, я не танцую
Тайпан, Agunda - Луна не знает пути
Different Heaven · EH!DE - My Heart
Qumu - Gourmet Race (From "Kirby Super Star")
Dion Timmer - Shiawase (VIP)
Alan Walker - Sing Me to Sleep
Post Malone · Swae Lee - Sunflower (Spider-Man: Into the Spider-Verse)
TheFatRat · Anjulie - Close To The Sun
Vicetone · Cozi Zuehlsdorff - Nevada (feat. Cozi Zuehlsdorff)
Stromae - Alors on danse (Radio Edit)
Defqwop - Heart Afire (feat. Strix) [Deleted NCS Release]
TheFatRat - Jackpot - FUM Version
Fall Out Boy - Centuries
TheFatRat · Laura Brehm - Monody
F-777 - The 7 Seas
Holder · GameChops - Spider Dance
The White Stripes - Seven Nation Army
The Animals - The House of the Rising Sun
Alphaville - Forever Young (2019 Remaster)
Europe - The Final Countdown (Lyrics)
Back in Black - Highway to Hell
AC/DC - Back In Black
K-391, Alan Walker & Ahrix - End Of Time (Lyrics)
Queen - We Will Rock You (Remastered 2011)
The White Stripes - Seven Nation Army
Aerosmith - Dream On
DV Street · ЛюSEA - Дороже золота
Capone - Oh No (TikTok Remix) Lyrics | Oh no, oh no, oh no no
Lost Sky · Jex - Where We Started
TheFatRat - Time Lapse
Tobu · Itro - Sunburst
K-391, Alan Walker, Tungevaag, Mangoo - Play
Потап и Настя - Не пара
Костюшкин Стас - Женщина, я не танцую
Zivert - Life
5sta Family - Я буду
Клава Кока - Покинула чат
Morandi - Angels (Love Is The Answer)
Моя Мишель - Зима в сердце
Натали · Натали - О, Боже, какой мужчина!
Dabro - Юность
SEREBRO - Мало тебя
Время и Стекло (Time & Glass) - Гармошка
Время и Стекло - На Стиле
Lost Frequencies · Janieck - Reality
Panic! At The Disco - House of Memories
Avicii · Sandro Cavazza - Without You
TheFatRat - Unity
Alan Walker - Alone
K-391 · Victor Crone - Lonely World
Avicii - Wake Me Up
Pascal Letoublon · Leony - Friendships (Lost My Love)
Imagine Dragons - Natural
AronChupa - 'I'm An Albatraoz
Rauf & Faik - Detstvo
Rauf & Faik - Ja ljublju tebja
Martin Arteta · creamy · Garrett Clark Borns - Past Lives
kostromin - моя голова винтом
LVNX · Ann Kovtun - Малиновый закат (Remix)
Mr_SadBoy - A Heart Full of Pain
MATRANG - Медуза
Анет Сай · Кокшаров Константин Николаевич · Баринов Никита Михайлович · Сайдалиева Анна Вячеславовна - СЛЁЗЫ (Из т/ш "Пацанки")
EMIN · JONY - Kamin
Kina · Adriana Proenza - Can We Kiss Forever?
sapientdream - Past Lives (slowed + reverb)
T3NZU - Drive Forever HQ Audio
Serhat Durmus - La Câlin
zxch. - past lives (lofi) // chillhop, relax, sleep, study ✨
Rauf & Faik - Vechera
Ernest Merkel - Шайлушай
RASA - Пчеловод
BAV - ПЧЕЛОБАВ УРОД
Dan Bull - Boom Boom Boom Boom Boom Boom Boom Boom Boom Boom Boom Boom Boom
David Guetta & Bebe Rexha - I'm Good (Blue) [Official Music Video]
Shouse - Love Tonight (Robin Schulz Remix)
NЮ - 18
Tones And I - Dance Monkey
Tommee Profitt · Fleurie · Mellen Gi - In The End (Mellen Gi Remix)
NЮ - Если сгорим
grandson - Blood // Water (Official Lyric Video)
Jim Yosef - Eclipse
K-391 - Summertime
Tobu - Candyland
Imagine Dragons - Bones
Rukkus - Classical VIP
Alan Walker - Spectre
Syn Cole - Feel Good
Toby Fox - MEGALOVANIA
TheFatRat · Slaydit · Anjulie - Stronger
twenty one pilots - Stressed Out
Marshmello - Alone
Клава Кока · NILETTO - Краш
Alan Walker · K-391 - PLAY
Владимир Высоцкий, Инструментальный ансамбль "Мелодия" - Утренняя гимнастика
Витас - 7 элемент
Ylvis - The Fox (What Does the Fox Say?)
NBSPLV - The Lost Soul Down
VØJ, Narvent - Memory Reboot (4K Music Video)
Clovis Reyes, HR, Irokz - Fluxxwave X EEYUH! (Official Audio)
TheFatRat - Xenogenesis
Aero Chord - Surface
Instupendo - Comfort Chain
hisohkah · WMD - School Rooftop
IcyBeast - 7 Weeks & 3 Days
Toby Fox - Fallen Down
CKay - love nwantiti (ah ah ah)
Elton John, Dua Lipa - Cold Heart (PNAU Remix) (Official Video)
Ed Sheeran - Bad Habits [Official Video]
Lost Frequencies · Calum Scott - Where Are You Now
LITTLE BIG - HYPNODANCER (Official Music Video)
Oliver Tree & Robin Schulz - Miss You [Official Music Video]
Shawn Mendes, Camila Cabello - Señorita
Nirvana - Smells Like Teen Spirit (Official Music Video)
Баста - Выпускной (Медлячок)
Imagine Dragons - Bad Liar – Stripped
Imagine Dragons - Believer
Little Big · Сергей Макаров · Илья Прусикин · Сергей Шишкарев - Every Day I'm Drinking
Little Big · Сергей Макаров · Илья Прусикин · Сергей Шишкарев - Life in Da Trash
Little Big · Сергей Макаров · Илья Прусикин · Сергей Шишкарев - With Russia from Love
Nirvana - Smells Like Teen Spirit
OneRepublic - Counting Stars
Sub Urban - Cradles
The Kid LAROI · Justin Bieber - STAY
BoyWithUke - Toxic
Powfu · beabadoobee - death bed (coffee for your head)
Aaron Smith · Krono · Luvli - Dancin (Krono Remix)
Oliver Tree - Jerk
DVRST - Close Eyes | Extended
NO BATIDÃO (SLOWED)
Irina Allegrova - S dnem rozhdeniya
Married Life - Up Soundtrack - Michael Giacchino (Extended) - Sleep | Study | Relax
PIZZA - Улыбка
RASA - ПОГУДИМ
XOLIDAYBOY - Моя хулиганка
Макс Корж - Малый повзрослел
Султан-Ураган · Мурат Тхагалегов - На дискотеку!..
Нейромонах Феофан - Топить за феофана
Нейромонах Феофан - Так и знай
Нейромонах Феофан - Хочу в пляс
Нейромонах Феофан - Изба ходит ходуном
Нейромонах Феофан - Мы валим боком на медведе (навалишная)
Нейромонах Феофан - Под драм легко
Нейромонах Феофан - Притоптать
Alexander Rybak - Fairytale
Jaymes Young - Infinity
Evanescence - Bring Me To Life
Fools Garden - Lemon Tree
Maroon 5 · Christina Aguilera - Moves Like Jagger (Studio Recording From "The Voice" Performance)
The Weeknd - Blinding Lights
Eurythmics · Annie Lennox · Dave Stewart - Sweet Dreams (Are Made of This)
Imagine Dragons - Thunder
twenty one pilots - Ride
GAYAZOV$ BROTHER$ · Filatov & Karas - Poshla zhara
K-391 & Alan Walker - Ignite (feat. Julie Bergan & Seungri)
Matthew Koma - Kisses Back (Official Video)
AURORA - Runaway
Indila - Dernière danse
Yiruma - River Flows in You
The Rare Occasions - Notion
Alice Merton - No Roots
Måneskin - Beggin'
Connie Francis - Pretty Little Baby
Alice Merton - No Roots
DJ Snake · Justin Bieber - Let Me Love You
Unlike Pluto · Mike Taylor - Everything Black (feat. Mike Taylor)
Alan Walker · Sophia Somajo - Diamond Heart
Dan Korshunov - Aurum
Post Malone, Swae Lee - Sunflower (Spider-Man: Into the Spider-Verse) (Official Video)
SEVDALIZA - ALIBI FT. PABLLO VITTAR & YSEULT (OFFICIAL MUSIC VIDEO)
Y2K, bbno$ - Lalala (Official Video)
The Kid LAROI, Justin Bieber - STAY (Official Video)
Charlie Puth - Attention [Official Video]
Ava Max - Sweet but Psycho [Official Music Video]
Glass Animals - Heat Waves (Official Video)
Lil Nas X - MONTERO (Call Me By Your Name) (Official Video)
Lil Nas X, Jack Harlow - INDUSTRY BABY (Official Video)
Lil Nas X - Old Town Road (Official Video) ft. Billy Ray Cyrus
David Guetta, Bebe Rexha & J Balvin - Say My Name (Lyric video)
Alice Deejay - Better Off Alone (Official Video)
Shakira - Waka Waka (This Time for Africa) (The Official 2010 FIFA World Cup™ Song)
O-Zone - Dragostea Din Tei [Official Video]
Ёлка - Прованс
Alan Walker - The Spectre
SEREBRO - Между нами любовь
DJ Snake · Lil Jon - Turn Down for What
Dabro - На часах ноль-ноль
Rauf & Faik · NILETTO - Если тебе будет грустно
Kostyashwarts - Макароны с кетчупом
Major Lazer & DJ Snake - Lean On (feat. MØ) [Official 4K Music Video]
TheFatRat, Slaydit & Anjulie - Stronger (Lyrics)
Major Lazer – Light it Up (feat. Nyla & Fuse ODG) (Remix) [Official 4K Music Video]
David Guetta · Bebe Rexha · J Balvin - Say My Name
Lucenzo · Don Omar - Danza Kuduro (Version MTO)
Dua Lipa - Levitating
Camila Cabello · Young Thug - Havana
Sean Paul · Dua Lipa - No Lie
Egzod · Maestro Chives - Royalty
T3NZU - Balenciaga
Ava Max - Kings & Queens
bearwolf · Василевская Валерия Алексеевна · Тамамян Арутюн Артакович - GODZILLA
ZHU - Faded
Konfuz · Маргарян Михаил Арманович - Кайф ты поймала
Грибы - Тает лёд
Ворую Алкоголь - FLOKI эвсе
GAZIROVKA · Озеров Никита Юрьевич · Ивашин Максим Викторович - Black
MORGENSHTERN - ПОЧЕМУ? (Official Video, 2022)
Masked Wolf - Astronaut In The Ocean (Official Music Video)
Макс Корж - Малый повзрослел (official video)
ARTIK & ASTI · Artem Kacher - Grustnyj dens
Лолита - На Титанике
Макс Корж - Жить в кайф
Dabro - Услышит весь район
DJ Snake - Let Me Love You ft. Justin Bieber
Alan Walker - Alone
K-391 & Victor Crone - Lonely World
Ed Sheeran - Shape of You (Official Music Video)
TheFatRat - Monody (feat. Laura Brehm)
K-391, Alan Walker & Ahrix - End of Time (Official Video)
Marshmello - Stars (Official Music Video)
Michael Jackson - Billie Jean (Official Video)
ABBA - Gimme! Gimme! Gimme! (A Man After Midnight)
Modern Talking - Brother Louie (Official Video)
Piano Fantasia - Song for Denise
Crazy Frog - Axel F (Official Video)
Tanir & Tyomcha - Da Da Da
Glass Animals · iann dior - Heat Waves
Oliver Tree - Life Goes On
SLAVA MARLOW - HOTEL TEBE SKAZAT...
SLAVA MARLOW - CAMRY 3.5
SLAVA MARLOW · MK - Net Problem
SLAVA MARLOW · Готлиб Артем Артемович · Савченко Олег Вадимович · ЛСП - Я НЕНАВИЖУ ЭТОТ ТРЕК!!! 凸 (￣ヘ￣)
SLAVA MARLOW · Готлиб Артём Артёмович - я не могу тебя найти (OST “Майор Гром: Игра”)
SLAVA MARLOW - TY GORISH' KAK OGON'
Rauf & Faik - Kolybel'naja
MORGENSHTERN · SLAVA MARLOW - Bystro
SLAVA MARLOW - Snova ja napivajus'
KNSRK - INSPIRED BY CRYSTALS
DVBBS · Borgeous - Tsunami (Radio Edit)
Armin van Buuren - Blah Blah Blah
Disfigure - Blank
TheFatRat - Xenogenesis
Janji · Johnning - Heroes Tonight
Imagine Dragons · Arcane · League Of Legends - Enemy (From the series Arcane League of Legends)
Burak Yeter · Danelle Sandoval - Tuesday (feat. Danelle Sandoval)
Lost Sky · Chris Linton - Fearless Pt. II
Martin Garrix - Animals (Radio Edit)
Tobu, Itro - Sunburst
Dynoro · Gigi D'Agostino - In My Mind
Cartoon · Jéja · Daniel Levi - On & On
Marshmello · Anne-Marie - FRIENDS
TheFatRat · Laura Brehm - Monody (Radio Edit)
Ария - Улица роз
КИНО - Звезда по имени Солнце (Remake)
Arija - Bespechnyy angel
The Chainsmokers - Don't Let Me Down (Official Video) ft. Daya
Alan Walker - The Spectre
TheFatRat - Fly Away feat. Anjulie
Marshmello - Alone (Official Music Video)
Marshmello - Together (Official Music Video)
Ласковый Май - Белые Розы
Руки Вверх - Крошка моя
Группа Белый День - Ах, мамочка, на саночках
IOWA - Маршрутка
Татьяна Куртукова - Матушка Земля, белая берёзонька
МакSим - Знаешь ли ты (официальный клип)
NЮ - Я надеюсь (Mood video)
Ирина Дубцова - Люби меня долго
MEDUZA, Becky Hill, Goodboys - Lose Control (Official Video)
NЮ - Выручай меня  (клип)
NЮ - Я тебя обидел (клип)
Alphaville - Forever Young (Official Music Video)
Pharrell Williams - Happy (Official Video)
Gotye - Somebody That I Used To Know (feat. Kimbra) [Official Music Video]
Fools Garden - Lemon Tree (Official HD Video)
Alec Benjamin - Let Me Down Slowly [Official Music Video]
Modern Talking - Cheri Cheri Lady
Alice DJ - Better Off Alone
Ace of Base - Happy Nation
A Touch Of Class - Around the World (La La La La La)
Alexandra Stan - Mr. Saxobeat (Radio Edit)
Little Big - Hypnodancer
Little Big - UNO
NЮ - Никто (Официальный клип, 2021)
Imagine Dragons - Thunder
Syn Cole - Feel Good | Future House | NCS - Copyright Free Music
Clarx - Zig Zag
Tobu - Candyland
TheFatRat · Laura Brehm - Monody
XOLIDAYBOY - Последний день на Земле
Моя Мишель - Зима в сердце (премьера клипа 2021)
NЮ — «Не получается»
Dua Lipa - Love Again (Official Music Video)
Ahxello - Frisbee
Morandi - Angels (Love Is The Answer)
Sappheiros - Away From Here
AP$ENT - Можно я с тобой?
Linkin Park - In The End (Mellen Gi & Tommee Profitt Remix)
LUM!X, Gabry Ponte - Monster (Official Music Video)
NЮ - Я надеюсь
Glass Animals - Heat Waves
NЮ - Я так тебя люблю
NЮ - Некуда бежать
Сердце земли моей - Руслан Алехно, Ирина Дорофеева
Toby Fox - NGAHHH!!
Toby Fox - Premonition
Toby Fox - Bonetrousle
Toby Fox - Shop
Toby Fox - sans.
Toby Fox - Uwa!! So Temperate♫
DJ Snake, Lil Jon - Turn Down for What
MORGENSHTERN - Я КОГДА-НИБУДЬ УЙДУ (Official Video, 2021)
Fifth Harmony - Worth It (Official Video) ft. Kid Ink
Willy William - Ego (Radio Edit)
Miyagi & Andy Panda - YAMAKASI (Official Video)
MORGENSHTERN - PABLO (Official Video, 2021)
MORGENSHTERN - OLALA (Official Video, 2021)
SLAVA MARLOW - Ты Горишь Как Огонь (ПРЕМЬЕРА КЛИПА)
MORGENSHTERN - DINERO (Official Video, 2021)
MORGENSHTERN - ICE
MORGENSHTERN - Я УБИЛ МАРКА
OXXXYMIRON — THE STORY OF ALISHER (Morgenshtern RIP)
IOWA - Одно и то же
АРИЯ — Улица Роз (1988)
Александр Ванюшкин · Оркестр Душа Баяна · Кубанский Казачий Хор - ТРИСТА ТРИДЦАТЬ ТРИ
Indila - Dernière Danse (Clip Officiel)
Adele - Set Fire to the Rain
POLNALYUBVI - Кометы (Official Music Video)
Lida · MORGENSHTERN - Цветы
Imagine Dragons - Believer (Official Music Video)
Coldplay - Hymn for the Weekend
Бабек Мамедрзаев - Принцесса (ПРЕМЬЕРА ХИТА 2019)
Татьяна Куртукова - Одного
Minelli - Rampampam
Imany - Don't Be so Shy (Filatov & Karas Remix)
Arthur Pirozhkov - Zacepila
Ласковый Май - Розовый вечер
Ласковый Май - Седая ночь
Dabro - Два крыла (премьера песни, 2023)
Dabro - На часах ноль-ноль (Official video)
Один в поле Воин
Bearwolf - GODZILLA (mood video)
Ace of Base - Happy Nation (Official Music Video)
Yiruma, (이루마) - River Flows in You
Marwill - Shake It! (Official Video)
RIVERO - Revolution (Extended Mix)
OneRepublic - I Ain’t Worried (Live From The Tonight Show Starring Jimmy Fallon)
Lilly Wood & The Prick · Robin Schulz - Prayer in C (Robin Schulz Radio Edit)
Elley Duhé - MIDDLE OF THE NIGHT
Masked Wolf - Astronaut In The Ocean
SLAVA MARLOW - СНОВА Я НАПИВАЮСЬ (Премьера Клипа! Хит 2020!)
Грибы - Тает Лёд
RASA  - Под фонарем
RASA · Kavabanga Depo Kolibri - Фиолетово
AronChupa, Little Sis Nora - I'm an Albatraoz (Audio)
Intelligency - August
Dschinghis Khan - Moskau (Russian, English, German & Spanish Lyrics)
Måneskin - I WANNA BE YOUR SLAVE
Boney M - Rasputin (Lyrics)
Gloria Gaynor - I Will Survive
MakSim - Znaesh` Li Ty
Юлия Савичева · Анастасия Максимова - Если в сердце живёт любовь
Clean Bandit - Symphony (feat. Zara Larsson) [Official Video]
MORGENSHTERN - День Х (Клип, 2024)
Alan Walker - Faded
Егор Крид - Сердцеедка (Премьера клипа, 2019)
Clean Bandit · Sean Paul · Anne-Marie - Rockabye (feat. Sean Paul & Anne-Marie)
Clean Bandit · Demi Lovato - Solo (feat. Demi Lovato)
ACTUAL World’s Smallest Violin with @ajr
Dynoro & Gigi D’Agostino - In My Mind
Клава Кока & NILETTO - Краш (official video)""".splitlines()

	if not file_lines:
		exit(-1)

	file_lines_length = len(file_lines) - 1

	start_input = input("Type start line index ( default is 1 ): ")

	start = end = 1

	if (start_input):
		if (start_input.isdecimal()):
			start = int(start_input)
		else:
			print(f"Invalid value in start line index: \"{start_input}\", expected integer. Using default.")
			
			start = 1
	else:
		start = 1

	end_input = input(f"Type end line index ( default for this file is {file_lines_length} ): ")

	if (end_input):
		if (end_input.isdecimal()):
			end = int(end_input)
		else:
			print(f"Invalid value in end: \"{end_input}\", expected integer. Using default.")
			
			end = file_lines_length
	else:
		end = file_lines_length

	if end < 1:
		print(f"Invalid value in end: {end}, expected end > 1, but end={end} < 1. Using default.")

		end = file_lines_length
	
	if start > end:
		print(f"Invalid value in start line index: {start}, expected start <= end, but start={start} > end={end}. Using default.")

		start = 1

	for line_number in range(start - 1, end):
		line = file_lines[line_number]

		print(f"{line_number + 1}: {line}")

		copy(line)

		print("Line has been copied!", end="")

		if (line_number < end - 1):
			input()