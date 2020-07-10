module Task2
  ( ConcurrentHashTable(..)

  , getCHT
  , newCHT
  , putCHT
  , sizeCHT
  ) where

import Control.Concurrent.STM (TVar, newTVar, readTVarIO)
import Control.Monad.STM (atomically)
import qualified Data.Map.Strict as Map (Map, empty)
import qualified Data.Vector as Vector (Vector, replicateM)

data ConcurrentHashTable k v = CHT
  { size :: TVar Int
  , storage :: TVar (Vector.Vector (TVar (Map.Map k v)))
  }

initCapacity :: Int
initCapacity = 197

-- | Constructs new 'ConcurrentHashTable'.
newCHT :: IO (ConcurrentHashTable k v)
newCHT = atomically $ do
  initSize    <- newTVar (0 :: Int)
  vector      <- Vector.replicateM initCapacity $ newTVar Map.empty
  initStorage <- newTVar vector
  pure $ CHT initSize initStorage

getCHT :: k -> ConcurrentHashTable k v -> IO (Maybe v)
getCHT = undefined

putCHT :: k -> v -> ConcurrentHashTable k v -> IO ()
putCHT = undefined

-- | Returns current @size@ of 'ConcurrentHashTable'.
sizeCHT :: ConcurrentHashTable k v -> IO Int
sizeCHT (CHT curSize _) = readTVarIO curSize
