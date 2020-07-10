module Task1
  ( WeekDay(..)

  , afterDays
  , daysToParty
  , isWeekend
  , nextDay
  ) where

-- | Type for days of the week.
data WeekDay
  = Sunday
  | Monday
  | Tuesday
  | Wednesday
  | Thursday
  | Friday
  | Saturday
  deriving (Show)

instance Enum WeekDay where
  toEnum day =
    case mod day 7 of
      0 -> Sunday
      1 -> Monday
      2 -> Tuesday
      3 -> Wednesday
      4 -> Thursday
      5 -> Friday
      6 -> Saturday
      -- | Not supposed to happen.
      _ -> error "Error occured in toEnum conversion of WeekDay"

  fromEnum Sunday    = 0
  fromEnum Monday    = 1
  fromEnum Tuesday   = 2
  fromEnum Wednesday = 3
  fromEnum Thursday  = 4
  fromEnum Friday    = 5
  fromEnum Saturday  = 6

instance Eq WeekDay where
  a == b = fromEnum a == fromEnum b

-- | Takes a 'WeekDay' and returns the next one
-- (the tomorrow day for a taken one).
nextDay
  :: WeekDay  -- ^ given 'WeekDay'
  -> WeekDay  -- ^ next 'WeekDay'
nextDay = succ

-- | Takes 'WeekDay' and number and returns a 'WeekDay'
-- that will be in given number of days.
afterDays
  :: WeekDay  -- ^ initial 'WeekDay'
  -> Int  -- ^ number of days from current 'WeekDay'
  -> WeekDay  -- ^ the resulting 'WeekDay'
afterDays day num = foldr (.) id (replicate (mod num 7) nextDay) day

-- | Takes a 'WeekDay' and shows whether it's a weekend.
isWeekend
  :: WeekDay  -- ^ 'WeekDay' to check
  -> Bool  -- ^ 'True' on weekend and 'False' otherwise
isWeekend Saturday = True
isWeekend Sunday   = True
isWeekend _        = False

-- | Takes a 'WeekDay' and returns number of days left until 'Friday'.
daysToParty
  :: WeekDay  -- ^ given 'WeekDay'
  -> Int  -- ^ number of day until 'Friday'
daysToParty day = mod (5 - fromEnum day) 7
