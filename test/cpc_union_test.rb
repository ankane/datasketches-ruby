require_relative "test_helper"

class CpcUnionTest < Minitest::Test
  def test_works
    sketch1 = DataSketches::CpcSketch.new(14)
    sketch1.update(1)
    sketch1.update(2.0)
    sketch1.update("three")

    sketch2 = DataSketches::CpcSketch.new(14)
    sketch2.update("three")
    sketch2.update(4)
    sketch2.update(5.0)

    u = DataSketches::CpcUnion.new(14)
    u.update(sketch1)
    u.update(sketch2)
    assert_in_delta 5, u.result.estimate
  end
end
