package models

import sorm._

/**
 * Created by caro
 */

object DB extends Instance(entities = Seq(Entity[Person]()), url = "jdbc:h2:mem:test")
