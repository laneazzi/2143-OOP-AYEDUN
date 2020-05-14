"""                   
 Author:    Olanrewaju Ayedun        
 Email:     Lanreayedunjr@gmail.com      
 Label:     P03/FINAL PROJECT       
 Title:     COVID 19 SIMULATOR  
 Course:    CMPS 2143 
 Semester:  Spring 2020

 Description:
          Corona beer simulator using pygame. Amateur plague inc.

 Usage:
       Customize config.json to change simulation variables

 Files:             simulation.py
                    config.json
                    Resources(Fonts and Images)
                    
                
"""

# Import and initialize the pygame library
import pygame
import random
import math
from datetime import datetime
import json
import os

class simulation():
    def __init__(self):
        self.days = 1
        self.infected = 0
        self.deaths = 0
        self.maxdays = 50

    # Function to increment days every 60 tick
    def set_days(self):
        self.days += 1

    def runsim(self, model):
        pygame.init()

        random.seed(datetime.now())
        # Project Name
        pygame.display.set_caption('Covid-19 Simulation')

        # Set up the drawing window
        screen = pygame.display.set_mode([Config["width"], Config["height"]])

        # sprites should be in a sprite group
        sprites_list = pygame.sprite.Group()

        # a list to hold all our sprites
        population = []

        # Set font
        font = pygame.font.Font('Roboto-Regular.ttf', 20)

        # loop N times
        for i in range(Config["population_count"]):
            # adds a "person" to our list of people
            # create an "instance" of our class
            population.append(Person(Config["width"], Config["height"], model.SIR[i],Config["sprite_width"],Config["sprite_height"],Config["sprite_speed"])) #random.choice(speeds)

            # Add last person to our sprites list
            # list[-1] give you the last item
            sprites_list.add(population[-1])  

        clock=pygame.time.Clock() # Used to control fps
        seconds = 0

        # Run until the user asks to quit
        running = True

        ## this is our simulation object??
        while running:

            # Did the user click the window close button?
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()
                    #print(pos)
                    population.append(Person(Config["width"], Config["height"], model.SIR[50],15,15,1,pos[0],pos[1])) #random.choice(speeds)

                    # Add last person to our sprites list
                    # list[-1] give you the last item
                    sprites_list.add(population[-1]) 


            # Fill the background with black
            screen.fill((20, 30, 30))

            # loop through each person
            # and call a move method
            for i in range(len(population)):
                population[i].move()

            # Check for collisions
            for j in range(len(population)):
                if population[i] != population[j]:
                    collided = population[i].checkCollide(
                        population[j])
                    if collided:
                        dx, dy = population[i].getDxDy()
                        population[j].setDxDy(dx * -1, dy * -1)

            # See if a person is ready to recover
            for i in range(len(population)):
                population[i].recover(self.days)

            sprites_list.draw(screen)

            # We will count the number infected each time
            for i in range(len(population)):
                if population[i].state == "infected":
                    self.infected += 1

            # Render the text and put it in a text box
            text = font.render("Day " + str(self.days) + " Infected: " + str(self.infected) 
            + " Deaths: " + str(self.deaths), 
            True, (30, 255, 30), (30, 30, 255))
            textbox = text.get_rect()

            # Set the boundaries for the textbox
            textbox.right = Config["width"]
            textbox.bottom = Config["height"]

            # Put the text on screen
            screen.blit(text, textbox)

            # Flip the display
            pygame.display.flip()

            # Advance a day every 60 ticks
            if seconds % 60 == 0:
                self.set_days()

                # Everyone infected has a chance to die once per day
                for i in range(len(population)):
                    if population[i].death() == True and population[i].state == "infected":
                        sprites_list.remove(population[i])
                        self.deaths += 1

            #Number of frames per second e.g. 60
            clock.tick(40) # 40 fps

            Config["myClock"] += 1
            seconds += 1
            self.infected = 0

            # If the number of days reaches a certain value, 
            # stop the sim
            if self.days > self.maxdays:
                running = False


# This class contains general information about the virus such as recovery time,
# infection radius, and more.
class virus():
    days_infected = 14
    fatality_rate = 5# percent out of 100
    infection_rate = 80 # used when people touch

# Class for creating an SIR model
class SIR_Model():
    SIR_images = {
        "yellow":  "pac_yellow.png",
        "red" :  "pac_red_blur.png",
        "green":  "pac_green.png",
    }

    def __init__(self):
        self.initial_infect = .20
        self.recovered_prob = .10
        self.susceptible_prob = .70
        self.SIR = []
    
    def make_model(self):

        S = ["S"] * int(self.susceptible_prob * 100)
        I = ["I"] * int(self.initial_infect * 100)
        R = ["R"] * int(self.recovered_prob * 100)

        self.SIR = S + I + R

        random.shuffle(self.SIR)

# Read in data from a json file into a dictionary
if os.path.isfile("config.json"):

    f = open("config.json", "r")

    data = f.read()

    Config = json.loads(data)

# Class to creating a person, control interaction with 
# environs, and assign image.
class Person(pygame.sprite.Sprite):
    # Constructor for person
    def __init__(self,
                 screen_width,
                 screen_height,
                 SIR,
                 width=15,
                 height=15,
                 speed=4,inx=None,iny=None):

        # Calls the parent class constructor
        super().__init__()

        self.id = Config["pid"]
        Config["pid"] +=1

        

        # screen width and height to know
        # when sprite hits screen bound
        self.screen_width = screen_width
        self.screen_height = screen_height

        # sprite size
        self.width = width
        self.height = height

        # direction x and y
        self.dx = 0
        self.dy = 0

        # Ensure Sprite Movement
        while self.dx + self.dy == 0:
            self.dx = random.choice([1, -1, 0])
            self.dy = random.choice([1, -1, 0])

        # amount of pixels per game loop
        self.speed = speed
        self.original_speed = speed

        # Assign color based on infection status
        if SIR == "S":
            self.state = "susceptible"
            self.color = "yellow"
            self.dayinfected = -999

        elif SIR == "I":
            self.state = "infected"
            self.color = "red"
            self.dayinfected = 1
        
        else:
            self.state = "recovered"
            self.color = "green"
            self.dayinfected = -999

        # To load the proper image for a state
        self.image = pygame.image.load(SIR_Model.SIR_images[self.color])
        
        # Picture Scaling
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        # Fetch the rectangle object that has the dimensions of the image.
        # Update the position of the object by setting the values
        # of rect.x and rect.y
        if inx is None:
            # creates a random location between bounds of screen size
            self.x = int(random.random() * self.screen_width)
        else:
            self.x = inx

        if iny is None:
            # creates a random location between bounds of screen size
            self.y = int(random.random() * self.screen_height)
        else:
            self.y = iny

        # sprite hitbox
        self.rect = self.image.get_rect(center=(self.x, self.y))

    # Set a person's direction
    def setDxDy(self, dx, dy):
        self.dx = dx
        self.dy = dy

    # Fetch a person's direction
    def getDxDy(self):
        return (self.dx, self.dy)

    # Change direction upon collision
    def changeDirection(self, sides_contacted):
        if sides_contacted["top"]:
            self.dy = 1
        if sides_contacted["bottom"]:
            self.dy = -1
        if sides_contacted["left"]:
            self.dx = 1
        if sides_contacted["right"]:
            self.dx = -1

    # Moves the sprites around
    def move(self):

        sides_contacted = self.checkWalls()

        self.changeDirection(sides_contacted)

        if self.dx < 0:
            self.rect.x -= self.speed
        elif self.dx > 0:
            self.rect.x += self.speed

        if self.dy < 0:
            self.rect.y -= self.speed
        elif self.dy > 0:
            self.rect.y += self.speed

    # This function checks the hitboxes of the sprites, to tell 
    # if a collison has occured and direction of collison
    # returns bool
    def checkCollide(self, other):
        sides_contacted = {
            "top": False,
            "bottom": False,
            "left": False,
            "right": False
        }

        if self.rect.colliderect(other.rect):

            if self.rect.top < other.rect.top:
                sides_contacted["bottom"] = True
                self.rect.y -= abs(self.rect.y - other.rect.y) // 8
            if self.rect.left < other.rect.left:
                sides_contacted["right"] = True
                self.rect.x -= abs(self.rect.x - other.rect.x) // 8
            if self.rect.right > other.rect.right:
                sides_contacted["left"] = True
                self.rect.x += abs(self.rect.x - other.rect.x) // 8
            if self.rect.bottom > other.rect.bottom:
                sides_contacted["top"] = True
                self.rect.y += abs(self.rect.y - other.rect.y) // 8
            
            infect_chance = random.randint(0, 100)

            # Calculate if people are infected or not
            if (infect_chance < virus.infection_rate and self.state == "susceptible" and 
            other.state == "infected"):
                self.state = "infected"
                self.color = "red"
                self.image = pygame.image.load(SIR_Model.SIR_images[self.color])
                self.image = pygame.transform.scale(self.image,(self.width, self.height))

            if (infect_chance < virus.infection_rate and other.state == "susceptible" and 
            self.state == "infected"):
                other.state = "infected"
                other.color = "red"
                other.image = pygame.image.load(SIR_Model.SIR_images[other.color])
                other.image = pygame.transform.scale(other.image,(other.width, other.height))

            
            self.changeDirection(sides_contacted) # To ensure movt upon # contact

            return True

        return False

    # This function makes sure the sprites will stay in screen boundary
    def checkWalls(self):
        sides = {"top": False, "bottom": False, "left": False, "right": False}

        if self.rect.top <= 0:
            sides["top"] = True
        if self.rect.left <= 0:
            sides["left"] = True
        if self.rect.right >= self.screen_width:
            sides["right"] = True
        if self.rect.bottom >= self.screen_height:
            sides["bottom"] = True

        return sides
    
    # Compute if an infected person dies each day.
    # And remove from game display if dead
    def death(self):
        dead = False
        die_chance = random.randint(0, 100)

        if die_chance < virus.fatality_rate and self.state == "infected":
            dead = True

        
        return dead

    # If a person has had the virus for a certain time, they will recover
    def recover(self, day):
        if day - self.dayinfected > virus.days_infected:
            self.state = "recovered"
            self.image = pygame.image.load(SIR_Model.SIR_images["green"])
            self.image = pygame.transform.scale(self.image,
                                                (self.width, self.height))
            

#__________________________________________________________________________
if __name__=='__main__':

    # Create instance of sim and model classes
    sim = simulation()
    model = SIR_Model()

    model.make_model() # To make SIR model

    sim.runsim(model) # Run Covid-19 Simulation

    # Done! Time to quit.
    pygame.quit()
