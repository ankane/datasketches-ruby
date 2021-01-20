require_relative "test_helper"

class CpcSketchTest < Minitest::Test
  def test_works
    sketch = DataSketches::CpcSketch.new(14)
    assert_equal 14, sketch.lg_k
    assert sketch.empty?

    sketch.update(1)
    sketch.update(2.0)
    sketch.update("three")
    assert_in_delta 3, sketch.estimate
    assert !sketch.empty?

    assert_in_delta 3, sketch.lower_bound(1)
    assert_in_delta 4, sketch.upper_bound(1)

    data = sketch.serialize
    assert_equal 40, data.bytesize

    sketch = DataSketches::CpcSketch.deserialize(data)
    assert_in_delta 3, sketch.estimate
  end

  def test_bignum
    sketch = DataSketches::CpcSketch.new(14)
    sketch.update(2**64)
  end
end
