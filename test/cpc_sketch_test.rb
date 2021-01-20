require_relative "test_helper"

class CpcSketchTest < Minitest::Test
  def test_works
    sketch = DataSketches::CpcSketch.new
    assert_equal 11, sketch.lg_k
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
    sketch = DataSketches::CpcSketch.new
    sketch.update(2**64)
  end
end
