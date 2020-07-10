{-# LANGUAGE InstanceSigs #-}

module Task8
  ( Config(..)
  , Grid(..)
  , ListZipper(..)

  , initGrid
  , showGrid
  , showNGrids
  , simulate
  ) where

import Control.Concurrent (threadDelay)
import Control.Monad (liftM2)
import System.Console.ANSI (cursorDownLine, cursorUpLine)
import System.Random (StdGen, mkStdGen, randomR, split)

class Functor w => Comonad w where
  extract :: w a -> a
  duplicate :: w a -> w (w a)
  extend :: (w a -> b) -> w a -> w b
  extend f = fmap f <$> duplicate

data ListZipper a = LZ [a] a [a]

listLeft :: ListZipper a -> ListZipper a
listLeft (LZ (a : as) x bs) = LZ as a (x : bs)
listLeft _                  = undefined

listRight :: ListZipper a -> ListZipper a
listRight (LZ as x (b : bs)) = LZ (x : as) b bs
listRight _                  = undefined

listWrite :: a -> ListZipper a -> ListZipper a
listWrite x (LZ as _ bs) = LZ as x bs

-- toList :: ListZipper a -> Int -> [a]
-- toList (LZ as x bs) n = reverse (take n as) <> [x] <> take n bs

instance Functor ListZipper where
  fmap f (LZ as x bs) = LZ (map f as) (f x) (map f bs)

iterateTail :: (a -> a) -> a -> [a]
iterateTail f = tail . iterate f

genericMove :: (z a -> z a) -> (z a -> z a) -> z a -> ListZipper (z a)
genericMove f g e = LZ (iterateTail f e) e (iterateTail g e)

instance Comonad ListZipper where
  extract :: ListZipper a -> a
  extract (LZ _ x _) = x

  duplicate :: ListZipper a -> ListZipper (ListZipper a)
  duplicate = genericMove listLeft listRight

newtype Grid a = Grid { unGrid :: ListZipper (ListZipper a) }

up :: Grid a -> Grid a
up (Grid g) = Grid (listLeft g)

down :: Grid a -> Grid a
down (Grid g) = Grid (listRight g)

left :: Grid a -> Grid a
left (Grid g) = Grid (fmap listLeft g)

right :: Grid a -> Grid a
right (Grid g) = Grid (fmap listRight g)

gridRead :: Grid a -> a
gridRead (Grid g) = extract $ extract g

gridWrite :: a -> Grid a -> Grid a
gridWrite x (Grid g) = Grid $ listWrite newLine g
  where
    oldLine = extract g
    newLine = listWrite x oldLine

horizontal :: Grid a -> ListZipper (Grid a)
horizontal = genericMove left right

vertical :: Grid a -> ListZipper (Grid a)
vertical = genericMove up down

instance Functor Grid where
  fmap f (Grid g) = Grid $ fmap f <$> g

instance Comonad Grid where
  extract :: Grid a -> a
  extract = gridRead

  duplicate :: Grid a -> Grid (Grid a)
  duplicate = Grid . fmap horizontal . vertical

neighbours :: [Grid a -> Grid a]
neighbours = horizontals <> verticals <> liftM2 (.) horizontals verticals
  where
    horizontals = [left, right]
    verticals   = [up, down]

-- | Stores parameters of 'Grid'.
data Config
  = Config
  { probabilty :: Double  -- ^ probability of infection
  , infectedDays :: Int  -- ^ infection period without symptoms in days
  , sickDays :: Int  -- ^ sickness period in days
  , immuneDays :: Int -- ^ immunity period in days
  }

-- | Status of Grid's cells.
data Status
  = Infected Int  -- ^ days the 'Cell' has left to be infected
  | Sick Int  -- ^ days the 'Cell' has left to be sick
  | Healthy Int  -- ^ days the 'Cell' has left to be healthy (0 days - vulnerable)
  deriving (Show)

-- | Single cell of 'Grid'.
data Cell
  = Cell
  { rand :: StdGen  -- ^ 'StdGen' to calculate probability
  , status :: Status  -- ^ 'Status' of 'Cell' at the moment
  } deriving (Show)

-- | Makes 'ListZipper' of 'Cell'. Similar to @genericMove@.
makeCellLZ
  :: (Cell -> Cell)  -- ^ function to create left list
  -> (Cell -> Cell)  -- ^ function to create right list
  -> Cell  -- ^ initial 'Cell'
  -> ListZipper Cell  -- ^ resulting infinite 'ListZipper'
makeCellLZ f g e = LZ (iterateTail f e) e (iterateTail g e)

-- | Generates new 'Cell' by splitting initial's 'Cell' 'StdGen'.
genCellLeft, genCellRight
  :: Cell  -- ^ initial 'Cell'
  -> Cell  -- ^ new 'Cell'
genCellLeft cell = cell { rand = fst $ split $ rand cell }
genCellRight cell = cell { rand = snd $ split $ rand cell }

-- | Generates new 'ListZipper' from initial one.
genZipperLeft, genZipperRight
  :: ListZipper Cell  -- ^ initial 'ListZipper'
  -> ListZipper Cell  -- ^ new 'ListZipper'
genZipperLeft = fmap genCellLeft
genZipperRight = fmap genCellRight

-- | The `magic` constant to avoid 'IO' interference on creating 'StdGen'.
-- Even though you might find the regularity in spreading while trying out
-- a lot of samples with this approach, simply changing this value would change
-- the outcome of same samples respectively.
magic :: Int
magic = 3221488

-- | Creates initial 'ListZipper' of 'Cell'. All cells are healthy
-- and vulnerable.
initZipper :: ListZipper Cell
initZipper =
  makeCellLZ genCellLeft genCellRight $ Cell (mkStdGen magic) $ Healthy 0

-- | Creates initial 'Grid' of 'Cell'. All cells are healthy and vulnerable
-- with only focusing 'Cell' being 'Infected'.
initGrid :: Config -> Grid Cell
initGrid cfg = gridWrite
  ((extract emptyGrid) { status = Infected $ infectedDays cfg })
  emptyGrid
  where
    emptyGrid = Grid $ genericMove genZipperLeft genZipperRight initZipper

-- | Applies specific function on all neighbours of focused element of 'Grid'.
applyOnNeighbours
  :: ([a] -> b)  -- ^ applying function's signature
  -> Grid a  -- ^ 'Grid' to work with
  -> b  -- ^ result of function application
applyOnNeighbours f g = f $ map (\dir -> extract $ dir g) neighbours

-- | Counts the amount of 'Infected' or 'Sick' cells in given list.
infectedCount
  :: [Cell]  -- ^ 'List' of cells to check (usually neighbours)
  -> Int  -- ^ Amount of not 'Healthy' cells
infectedCount cells = foldr ((+) . isDangerous . status) 0 cells

-- | Shows whether 'Status' is dangerous or not.
isDangerous
  :: Status  -- ^ given 'Status'
  -> Int  -- ^ @0@ if 'Healthy' and @1@ otherwise
isDangerous (Healthy _) = 0
isDangerous _           = 1

-- | Rule to update the cells of 'Grid' on every simulation.
rule
  :: Config  -- ^ 'Config' of current 'Grid'
  -> Grid Cell  -- ^ given 'Grid' itself
  -> Cell  -- ^ new 'Cell' updated by the rule
rule cfg g = case status $ cell of
  Healthy  0 -> testYourLuck cfg g
  Infected 0 -> cell { status = Sick $ sickDays cfg }
  Sick     0 -> cell { status = Healthy $ immuneDays cfg }
  _          -> cell { status = decreaseDays $ status cell }
  where
    cell = extract g

-- | Decreases days the 'Cell' has left to stay in current 'Status'.
-- It is expected that @n > 0@.
decreaseDays
  :: Status  -- ^ initial 'Status'
  -> Status  -- ^ same 'Status' with decreased days.
decreaseDays (Healthy  n) = Healthy $ n - 1
decreaseDays (Infected n) = Infected $ n - 1
decreaseDays (Sick     n) = Sick $ n - 1

-- | Applied on vulnerable Cells, this function returns the result
-- of focused 'Cell' interacting with not 'Healthy' neighbours.
testYourLuck
  :: Config  -- ^ 'Config' of current 'Grid'
  -> Grid Cell  -- ^ 'Grid' to work with
  -> Cell  -- ^ updated focused 'Cell'
testYourLuck cfg g =
  iterate (updateCell cfg) (extract g) !! applyOnNeighbours infectedCount g

-- | Updates 'Cell'\'s 'StdGen' and it's 'Status' according to probability
-- of current 'Grid'\'s infection.
updateCell
  :: Config  -- ^ 'Config' of current 'Grid'
  -> Cell  -- ^ 'Cell' to upgrade
  -> Cell  -- ^ updated 'Cell'
updateCell cfg cell =
  Cell (snd $ getRand cell) $ if probabilty cfg > (fst $ getRand cell)
    then Infected $ infectedDays cfg
    else Healthy 0

-- | Returns pair of 'Cell'\'s random probability and new 'StdGen'.
getRand
  :: Cell  -- ^ Cell to generate pair for
  -> (Double, StdGen)  -- ^ resulting 'Double' and new 'Stdgen'
getRand cell = randomR (0.0, 1.0) $ rand cell

-- | Simulates one day of infections on given 'Grid'.
simulate
  :: Config  -- ^ 'Config' of current 'Grid'
  -> Grid Cell  -- ^ 'Grid' to work with
  -> Grid Cell  -- ^ next iteration of given 'Grid'
simulate cfg = extend (rule cfg)

-- | Shows 'Grid' of 'Cell' in given radius around focused 'Cell'.
showGrid
  :: Int  -- ^ radius around focused 'Cell' to show
  -> Grid Cell  -- ^ 'Grid' to display
  -> IO ()  -- ^ real world to print the result
showGrid n (Grid g) = mapOnZipper printZipper g
 where
  mapOnZipper
    :: (ListZipper Cell -> IO ()) -> ListZipper (ListZipper Cell) -> IO ()
  mapOnZipper f (LZ as x bs) = do
    mapM_ f (reverse $ take n as)
    _ <- f x
    mapM_ f (take n bs)

  printZipper :: ListZipper Cell -> IO ()
  printZipper (LZ as x bs) = do
    putStrLn $ showStatus (reverse $ take n as)
            <> showStatus [x]
            <> showStatus (take n bs)

-- | Takes 'List' of 'Cell' and returns it's 'String' representation.
showStatus
  :: [Cell]  -- ^ 'List' to represent
  -> String  -- ^ resulting 'String'
showStatus (a : as) = case status a of
  Healthy  0 -> " " <> showStatus as
  Healthy  _ -> "@" <> showStatus as
  Infected _ -> "#" <> showStatus as
  Sick     _ -> "#" <> showStatus as
showStatus [] = ""

-- | Shows @n@ simulations of given 'Grid'.
showNGrids
  :: Int  -- ^ amount of iterations to show.
  -> Int  -- ^ radius of showing to transfer to @showGrid@
  -> Config  -- ^ 'Config' of current 'Grid'
  -> Grid Cell  -- ^ 'Grid' to print
  -> IO ()  -- ^ Real world to print result
showNGrids 0 d _ _ = do
  cursorDownLine $ 2 * d + 1
  return ()
showNGrids n d cfg g = do
  showGrid d g
  threadDelay 500000
  cursorUpLine $ 2 * d + 1
  showNGrids (n - 1) d cfg $ simulate cfg g

{- Usage sample:
cfg = Config 0.25 1 2 4
grid = initGrid cfg
nextGrid = simulate cfg grid

showGrid 5 grid
showGrid 5 nextGrid
  | | | | |
  equal to
  | | | | |
showNGrids 2 5 cfg grid

showNGrids 50 25 cfg grid
-}
