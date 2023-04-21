from queue import dist
from queue.step import step_model
from queue.event import event_model


def main():
    a, b = 1, 10
    generator = dist.EvenDistribution(a, b)

    lam = 4
    processor = dist.ExponentialDistribution(lam)

    total_tasks = 1000
    repeat_percentage = 0
    step = 0.01

    print('step_model:', step_model(generator, processor, total_tasks, repeat_percentage, step))
    print('event_model:', event_model(generator, processor, total_tasks, repeat_percentage))


if __name__ == '__main__':
    main()
