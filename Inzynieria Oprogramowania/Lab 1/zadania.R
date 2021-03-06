#Zad 1
45 * 678
x <- c(7,4,2,0,9)
y <- c(2,1,5,3,3)
sumaWektorow <- x+y
sumaWektorow
x * y
A <- matrix(c(0,1,5,2,6,0,1,4,3), nrow = 3, ncol = 3)
A
B <- matrix(c(9,1,4,8,2,9,7,7,2), nrow = 3, ncol = 3)
B
A %*% B
suma <- function(a,b) {
  a + b
}
suma(A, B)
suma(2,5)

#Zad 2
#setwd , getwd
dane <- read.table("osoby.csv", header=TRUE, sep=",")
dane
dane[,"imie", drop=FALSE] #dane[, 2, drop=FALSE], dane$imie
subset(dane, plec == "k") #dane[dane[, "plec"]=="k"], dane[which(osoby$plec == "k")]
write.table(subset(dane, plec == "m" & wiek > 50), file="osoby2.csv")

#Zad 3
#dane$wyplata <- sample(2000:5000, size = nrow(dane), replace = TRUE)
dane$wyplata <- round(runif(nrow(dane), 2000, 5000), 2) #dane$wyplata <- sample(seg(from=2000, to=5000, by=0.1),size=nrow(osoby))
dane
newUser <- data.frame(nazwisko = "Kowalski", imie = "Jan", plec = "m", wiek = "30", wyplata = 2212.22)
dane <- rbind(dane, newUser)
mean(dane$wyplata)
sd(dane$wyplata)
min(dane$wyplata)
max(dane$wyplata)
dane$std_wyplata <- (dane$wyplata - mean(dane$wyplata))/sd(dane$wyplata)
dane$norm_wyplata <- (dane$wyplata - min(dane$wyplata))/(max(dane$wyplata)-min(dane$wyplata))
dane
summary(dane$wiek)

standarize(dane$wyplata)
normalize(dane$wyplata)