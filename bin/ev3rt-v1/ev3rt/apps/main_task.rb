class Detector
  
  def initialize
    @sonar_sensor = EV3RT::SonarSensor.new(EV3RT::PORT_2)
    @led = EV3RT::LED.new()
  end

  def measure
    if @sonar_sensor.distance <= 30
      @led.on(EV3RT::LED_GREEN)
    else
      @led.off
    end
  end
  
end

class MainTask

  def self.execute
    self.new.execute
  end

  def initialize
    @detector = Detector.new()

  end

  def execute
    while true
      @detector.measure
      EV3RT::Task.sleep(1000)
    end
  end
end

MainTask.execute


