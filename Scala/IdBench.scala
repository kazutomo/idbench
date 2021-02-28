// JAVA_OPTS="-Xmx4G" scala IdBench.scala
// or
// scalac IdBench.scala; JAVA_OPTS="-Xmx4G" scala

object IdBench {
  def main(args: Array[String]) {
    val n = 1<<25
    val m = 8
    val niters = n*m
    var sum:Double = 0.0
    var idx:Int = 0

    // initialize data
    val data = Array.tabulate(n) {i => ((i+1)%n).toDouble}

    // main loop
    val st = System.nanoTime()
    for (i <- 0 until niters) {
      idx = data(data(data(data(idx).toInt).toInt).toInt).toInt
      sum += idx
    }
    val et = System.nanoTime() - st

    // stats
    val a = et/niters.toDouble
    println(f"Elapsed [msec]: " + (et*1e-6))
    println(f"Per iteration [nsec]: $a")
    println(f"sum=$sum")
    val ref = m.toDouble * n.toDouble * (n.toDouble-1.0) / 2.0.toDouble;
    if ( (sum-ref).abs < 1e-6) {
      println(f"Failed to validate: sum should be $ref")
    } else {
      println("Validation passed!")
    }
  }
}
